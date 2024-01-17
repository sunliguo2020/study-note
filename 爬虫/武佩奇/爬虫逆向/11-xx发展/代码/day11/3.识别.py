# @课程    : 爬虫逆向实战课
# @讲师    : 武沛齐
# @课件获取 : wupeiqi666
# pip install ddddocr

import requests
import ddddocr

res = requests.get(url="https://xuexi.chinabett.com/Login/GetValidateCode/1701954700567")
# with open("code.png", mode='wb') as f:
#     f.write(res.content)

ocr = ddddocr.DdddOcr(show_ad=False)
code = ocr.classification(res.content)
print(code)
