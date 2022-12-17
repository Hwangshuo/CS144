#include "stream_reassembler.hh"

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
    if (!eof) {
        if (Reassemble_index == index) {  // 如果到达的包是顺序的
            if (data.size() + Unassemble_buffer.size() + Reassemble_buffer.size() > _capacity)  // 无法存放到达的包
            {
                // 丢包
            } else  // 可以存放到达的包
            {
                Reassemble_index = index;
                for (int i = 0; i < data.size(); i++)
                    Reassemble_buffer.push_back(data[i]);
                Reassemble_size += data.size();
            }
        } else {
            Unassemble_index.push_back(index);
            for (int i = 0; i < data.size(); i++)
                Unassemble_buffer.push_back(data[i]);
            Unassemble_size += data.size();
        }
    }

    for(int i=0;i<Unassemble_index.size();i++)
    {
        if(Unassemble_index[i]==Reassemble_index)
        {
            string str;
            
        }
    }
}

size_t StreamReassembler::unassembled_bytes() const { return {}; }

bool StreamReassembler::empty() const { return {}; }
