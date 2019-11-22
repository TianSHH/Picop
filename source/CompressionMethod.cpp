#include "CompressionMethod.h"

void CompressionMethod::drawHuffmanTree(QImage inputImage)
{
    HuffmanNode *node;
    huffman(node);
    HuffmanCode *code;
    huffmanCode(node, code);

} // drawHuffmanTree

int *CompressionMethod::getPixel(QImage inputImage)
{
    int width = inputImage.width();
    int height = inputImage.height();

    // index 0-255 => pixel
    // index 256   => total number of pixels
    int *arr = new int[256];

    for (int i = 0; i <= 256; i++)
        arr[i] = 0;
    arr[256] = width * height;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int gray = qGray(inputImage.pixel(i, j));
            arr[gray]++;
        }
    }

    return arr;
} // getPixel

void CompressionMethod::huffman(HuffmanNode *node)
{

    // 初始化
    for (int i = 0; i < 2 * 255 - 1; i++)
        node[i].init();

    int *pixel = getPixel(inputImage);

    for (int i = 0; i <= 255; i++)
    {
        node[i].gray = i;
        node[i].weight = pixel[i] / pixel[256];
    }

    for (int i = 255; i < 2 * 255 - 1; i++)
    {
        int minIndex = 0;
        int secMinIndex = 0;

        int minVal = __FLT_MAX__;
        int secMinVal = __FLT_MAX__;

        for (int j = 0; j < i; i++)
        { // 选出两个权值最小的根节点
            if (node[j].parent == -1)
            {
                if (node[j].weight < minVal)
                {
                    secMinVal = minVal;
                    minVal = node[j].weight;
                    secMinIndex = minIndex;
                    minIndex = j;
                }
                else if (node[j].weight < secMinVal)
                {
                    secMinVal = node[j].weight;
                    secMinVal = j;
                }
            }
        }

        node[minIndex].parent = i;
        node[secMinIndex].parent = i;
        node[i].lChild = minIndex;
        node[i].rChild = secMinIndex;
        node[i].weight = node[minIndex].weight + node[secMinIndex].weight;
    }

} // huffman

void CompressionMethod::huffmanCode(HuffmanNode *node, HuffmanCode *code)
{
}