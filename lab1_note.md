## **CS144实验记录（Lab1）**

### **Lab Checkpoint 1: stitching substrings into a byte stream**

In Lab 1, you’ll implement a stream reassembler —a module that stitches small pieces of the byte stream (known as substrings, or segments) back into a contiguous stream of bytes in the correct sequence.

#### **Putting substrings in sequence**

我们根据作业的要可以看出这一张是要设计一个重组器，在真实场景中就是将对端发送的经过分片后的一系列IP数据包进行重组，这些数据包可能出现乱序，丢失或者重传，在本次作业中我们只需要将一系列的string data重组存放进大小为capacity的buffer中，buffer中包括已经成功重组的部分和待排序的部分
```C++
public class Apple {
  public Apple() {}
}
```
