#include "stream_reassembler.hh"

#include <iostream>

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&.../* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity) {}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    // DUMMY_CODE(data, index, eof);
    // 实现TCP组包功能
    if (eof) {
        _eof = true;
        eof_index = index + data.size();
    }

    int flag1 = 0;
    for (size_t i = 0; i < Unassemble_buffer.size(); i++) {
        if (index + data.size() < Reassemble_index) {
            flag1 = 1;
        } else if (index <= Unassemble_index[i] &&
                   index + data.size() >= Unassemble_buffer[i].size() + Unassemble_index[i]) {
            Unassemble_index.erase(Unassemble_index.begin() + i);
            Unassemble_size -= Unassemble_buffer[i].size();
            Unassemble_buffer.erase(Unassemble_buffer.begin() + i);
            i--;
            flag1 = 0;

        } else if (index >= Unassemble_index[i] &&
                   index + data.size() <= Unassemble_buffer[i].size() + Unassemble_index[i]) {
            flag1 = 1;
        } else if (index <= Unassemble_index[i] + Unassemble_buffer[i].size() &&
                   index + data.size() > Unassemble_index[i] + Unassemble_buffer[i].size()) {
            Unassemble_index.push_back(Unassemble_index[i] + Unassemble_buffer[i].size());
            Unassemble_buffer.push_back(
                data.substr(Unassemble_index[i] + Unassemble_buffer[i].size() - index,
                            data.size() - (Unassemble_index[i] + Unassemble_buffer[i].size() - index)));
            Unassemble_size -= data.size() - (Unassemble_index[i] + Unassemble_buffer[i].size() - index);
            flag1 = 1;
        }
    }
    if (!flag1) {
        Unassemble_index.push_back(index);
        Unassemble_buffer.push_back(data);
        Unassemble_size += data.size();
    }

    // 开始进行重组和发包
    int flag = 0;
    int k;
    while (true) {
        k = 0;
        flag = 0;
        for (size_t i = 0; i < Unassemble_index.size(); i++, k++) {
            if (Reassemble_index >= Unassemble_index[i] &&
                Reassemble_index <= (Unassemble_index[i] + Unassemble_buffer[i].size())) {
                Unassemble_size -= Unassemble_buffer[i].size();
                for (size_t j = Reassemble_index - Unassemble_index[i]; j < Unassemble_buffer[i].size();
                     j++) {
                    Reassemble_buffer.push_back(Unassemble_buffer[i][j]);
                }
                Reassemble_index = Unassemble_index[i] + Unassemble_buffer[i].size();
                Unassemble_buffer.erase(Unassemble_buffer.begin() + k);
                Unassemble_index.erase(Unassemble_index.begin() + k);
                flag = 1;
            }
        }
        if (flag == 0 || Unassemble_index.size() == 0)
            break;
    }  // 重组完成
    std::string stream;
    stream.assign(Reassemble_buffer.begin(), Reassemble_buffer.end());
    Reassemble_index = Reassemble_index - (stream.size() - _output.write(stream));
    stream.clear();
    // Reassemble_buffer.clear();
    size_t Reassemble_size = Reassemble_buffer.size();
    for (size_t i = 0; i < Reassemble_size; i++) {
        Reassemble_buffer.pop_front();
    }

    if (_output.bytes_written() == eof_index && _eof)
        _output.end_input();
}
size_t StreamReassembler::unassembled_bytes() const { return Unassemble_size; }

bool StreamReassembler::empty() const { return Unassemble_size == 0; }
