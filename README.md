# NetWorkDisk

使用C++语言实现一个网盘项目，数据库使用Mysql，代码编写使用Qt

## Day01：

**搭建客户端与服务器**

## Day02：

**通信协议设计**

协议结构体设计：

| 协议设计     | 命名      |
| ------------ | --------- |
| 总的消息大小 | uiPDULen  |
| 消息类型     | uiMsgType |
| 实际消息大小 | uiMsgLen  |
| 实际消息     | caMsg     |

```
struct PDU
{
    uint uiPDULen;      // 总的协议数据单元大小
    uint uiMsgType;     // 消息类型
    char caData[64];    // 数组（文件其他信息，文件名等）
    uint uiMsgLen;      // 实际消息长度
    int caMsg[];        // 实际信息
};
```
## Day03：
**连接数据库Mysql**
