# 安装

```python
pip install djangorestframework
```

# settings.py 中添加

```
INSTALLED_APPS = {
	'rest_framework'
}
```

# Serializer类和ModelSerializer类进行序列化操作

## .1创建模型类文件

##  .2创建序列化文件 app/serializers.py

```python
from rest_framework import serializers
class GoodsCategorySerializer(serializers.Serializer):
    id = serializers.IntegerField(read_only=True)
    name = serializers.CharField()
```

## .3 创建视图类

```python
class GoodsView(APIView):
    def get(self, request, *args, **kwargs):
        # 获取queryset
        goods = Goods.objects.all()[:10]
        # 开始序列化多条数据，加上many=True
        goods_json = GoodsSerializer(goods, many=True)
        #goods_json = GoodsModelSerializer(goods, many=True)
        # 返回序列化对象。goods_json.data 是序列化后的值
        print(goods_json.data)

        return Response(goods_json.data)
```

## .4 配置路由并运行

```

```



