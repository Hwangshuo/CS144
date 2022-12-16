#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) { _capacity = capacity; }

size_t ByteStream::write(const string &data) { //将字符串data写进我们设置的buffer中，

    int write_bytes;//要写入buffer的字节数
    if (data.size() > remaining_capacity()) {
        write_bytes = remaining_capacity();
    } else {
        write_bytes = data.size();
    }//若要写入buffer的流字节数大学剩余空间，则只能写入有限个字节，as fit as well
    for (int i = 0; i < write_bytes; i++) {
        pkt_buffer.push_back(data[i]);
    }
    totalWrite += write_bytes;//统计总共写入的字节数量
    return write_bytes;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {

    string str;
    int read_bytes;//同上，将buffer中的size与要读的len作对比
    if (len > pkt_buffer.size())
        read_bytes = pkt_buffer.size();
    else
        read_bytes = len;
    str.assign(pkt_buffer.begin(), pkt_buffer.begin() + read_bytes);

    return str;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {

    if (len > pkt_buffer.size()) {
        pkt_buffer.clear();
        totalPop += pkt_buffer.size();
    }

    else {
        for (long unsigned int i = 0; i < len; i++)
            pkt_buffer.pop_front();
        totalPop += len;
    }
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {

    string str;
    str = ByteStream::peek_output(len);
    ByteStream::pop_output(len);
    return str;
}

void ByteStream::end_input() { end = true; }

bool ByteStream::input_ended() const { return end; }

size_t ByteStream::buffer_size() const { return pkt_buffer.size(); }

bool ByteStream::buffer_empty() const { return pkt_buffer.size() == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return totalWrite; }

size_t ByteStream::bytes_read() const { return totalPop; }

size_t ByteStream::remaining_capacity() const { return _capacity - pkt_buffer.size(); }