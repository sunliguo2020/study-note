在Python中，你可以使用base64模块来解码base64编码的字符串，并将其转换为图片。通常，base64编码的字符串会嵌入在某种数据格式中，如JSON或XML，其中也会指定图片的格式（如PNG或JPEG）。

下面是一个简单的例子，说明如何将base64编码的字符串转换为PNG图片：
```python
python
import base64  
import io  
from PIL import Image  
  
# 假设你有一个base64编码的字符串，它代表一个PNG图片  
base64_str = "iVBORw0KGgoAAAANSUhEUgAAAAUAAAAFCAYAAACNbyblAAAAHElEQVQI12P4//8/w38GIAXDIBKE0DHxgljNBAAO9TXL0Y4OHwAAAABJRU5ErkJggg=="  
  
# 去除base64字符串中的前缀（如果有的话），只保留实际编码部分  
# 注意：这取决于你的base64字符串是如何格式化的。在某些情况下，你可能不需要这一步。  
# base64_str = base64_str.split(',')[1]  # 如果你的字符串是"data:image/png;base64,..."这样的格式  
  
# 解码base64字符串为字节数据  
decoded_bytes = base64.b64decode(base64_str)  
  
# 使用PIL库将字节数据转换为图片  
image = Image.open(io.BytesIO(decoded_bytes))  
  
# 显示图片（如果你在一个支持图形界面的环境中）  
image.show()  
  
# 如果你想要保存图片到文件  
image.save('output.png')
```
在这个例子中，我们首先使用base64.b64decode()函数将base64编码的字符串解码为字节数据。然后，我们使用PIL库（Python Imaging Library，也被称为Pillow）的Image.open()函数，配合io.BytesIO()来将这些字节数据转换为一个图片对象。最后，我们可以使用show()方法显示图片，或者使用save()方法将其保存为文件。