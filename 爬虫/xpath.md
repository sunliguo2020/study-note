| 表达式                       | 描述                                        | 示例                                                         |
| ---------------------------- | ------------------------------------------- | ------------------------------------------------------------ |
| //node_name                  | 在文档中选择所有匹配node_name的节点         | //div (选择文档中所有的div对象)                              |
| /node_name                   | 选择当前或前序元素中所有匹配node_name的节点 | //div/ul (选择素有div内ul对象)                               |
| @attr                        | 选择一个元素的属性                          | //div/ul/@class (选择素有div中ul对象的class属性)             |
| ../                          | 选择父元素                                  | //ul/../ （选择素有ul元素的父元素）                          |
| text()                       | 从节点或元素中选择文本                      | //div[@id="mylists"]/ul/li/text() (选择ID为“mylists"的div中列表中元素的文本) |
| contains(@attr,"value")      | 选择属性具有特定值的元素                    | //div[contains(@id,"list")] (选择所有ID中有”list“的div)      |
| *                            | 通配符                                      | //div/ul/li/* （选择所有的div中ul中列表对象的后继            |
| [1,2,3..] [last()] [first()] | 根据在节点中出现的顺序选择元素              | //div/ul/li[3] (选择所有div中ul中的第三个列表对象)           |

示例：

//title[@lang]	选取所有拥有名为lang的属性的title元素

//title[@lang='eng']	选取所有title元素，且这些元素拥有值为eng的lang属性 **属性筛选，@属性名=值**

//@lang	选取名为lang的所有属性

