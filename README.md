# Huffman Compression Software
> 2024 Winter 数据结构课程设计
```
5、哈夫曼压缩软件设计
【问题描述】
采用哈夫曼树求得的用于通信的二进制编码称为哈夫曼编码。利用哈夫曼编码对文本或图像进行数据压缩，设计数据压缩软件。
【设计要求】
设计基于哈夫曼编码的文本和图像压缩软件。
（1）采用静态链表的二叉树等数据结构。
（2）可以随机、文件及人工输入数据。
（3）创建哈夫曼树，生成哈夫曼编码和译码。
（4）源码、编码和压缩后的信息均以文件形式保存。
（5）可以查询和更新数据。
（6）其它完善性或扩展性功能。
```
该项目实现了一个轻量级的C++哈夫曼压缩软件，具体来说是后端的哈夫曼算法和压缩文件生成，前端显示用户界面进行输入和展示操作
## Quick Start
- 运行server.cpp
- 将index.html拖入Chrome浏览器中，用浏览器打开该文件
## 我们需要做什么：
### 1. Liusi & Haoyuan
- 读懂并跑通主程序encoder_decoder.cpp
- 按照注释中的要求，完成所有C++文件中注释有TODO的函数(可以在每个c++文件中测试能不能跑通)
- 为边缘样例完善、保护程序（比如输错了怎么办、函数运行有问题怎么办）
- 提出代码可以改进的地方，比如怎样更快更高效。（非必须）
  > 如果直接能写，写日志之后直接实现即可，不会写的可以仅提出想法
### 2. Qianqian
- 完善前后端通信、功能的连接
### 3. 🙋如果你有疑问
请及时联系Qianqian，无论是什么问题。期待良好的合作。
### 4. 为项目做贡献
请提交修改内容或者新增加的内容到新的分支，不要直接修改主分支
### 5. 时间
- 12.15日晚上22:00之前完成主体内容
- 12.16-12.18：完善内容，完成整个软件
## 开发日志
### 12.11
- Qianqian: 完成了主要的哈夫曼算法、一些输入函数和前端视图
- Haoyuan：完成了关于图片编码和解码的相关函数（io.cpp中的四个函数）
