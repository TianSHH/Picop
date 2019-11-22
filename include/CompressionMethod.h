#ifndef COMPRESSIONMETHOD_H
#define COMPRESSIONMETHOD_H

#include <QtGui/QImage>

// huffman 树结点
struct HuffmanNode
{
    int gray;     // 像素出现的次数
    float weight; // 权重
    int lChild, rChild, parent;
    double idx, idy;

    // 节点初始化
    void init()
    {
        gray = -1;
        parent = -1;
        lChild = -1;
        rChild = -1;
    }
};

struct HuffmanCode
{
    char bits[255];
    int start;
    int gray;
};

class CompressionMethod
{
public:
    void drawHuffmanTree(QImage inputImage);

public:
    int *getPixel(QImage inputImage);

    void huffman(HuffmanNode *node); // 建立 Huffman 树
    void huffmanCode(HuffmanNode *node, HuffmanCode *code);
};

#endif // COMPRESSIONMETHOD_H