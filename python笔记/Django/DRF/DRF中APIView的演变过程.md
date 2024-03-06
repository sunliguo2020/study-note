## 基础版

- 创建serializer类，如果要添加或者修改数据，需要重写create和update方法
- 类视图继承APIView，get和 post方法

1、创建序列化类

```python
class UserSerializer(serializers.Serializer):
    username = serializers.CharField()
    email = serializers.EmailField()
    groups = serializers.CharField()
```

2、继承APIView

```python
class UserAPIView(APIView):
    def get(self, request):
        # 从模型类中获取数据
        queryset = User.objects.all()
        # 构建序列化对象
        serializer = UserSerializer(queryset, many=True)
        # 返回结果
        return Response(serializer.data)
    def post(self, request):
        """
         处理POST请求，并返回响应。
         """
        # 从请求中获取数据，并转换为序列化器验证所需的格式
        data = request.data

        # 初始化序列化器
        serializer = UserSerializer(data=data)

        # 验证数据
        if serializer.is_valid():
            # 如果数据验证通过，保存实例
            serializer.save()
            # 返回成功响应
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        else:
            # 如果数据验证失败，返回错误响应
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

```

重写create和update方法

```python
class UserSerializer(serializers.Serializer):
    username = serializers.CharField()
    email = serializers.EmailField()
    groups = serializers.CharField()

    def create(self, validated_data):
        """
        创建并返回一个新的模型实例
        :param validated_data: 
        :return: 
        """
        # 使用validated_data 来创建模型实例
        s_obj = User.objects.create(**validated_data)

        return s_obj

    def update(self, instance, validated_data):
        """
        更新一个已存在的模型实例
        :param instance:已经存在的模型实例
        :param validated_data:
        :return:
        """
        instance.field1 = validated_data.get('field1', instance.field1)
        
        # 保存模型实例
        instance.save()
        # 返回更新后的模型实例
        return instance

```

### 总结：

- 上面的get方式没有实现分页

## GenericAPIView 

实现的功能：

类属性：

- queryset
- serializer_class
- lookup_field
- lookup_url_kwarg
- pagination_class
- paginator pagination_class的实例

方法：

- get_queryset()
- get_object()
- get_serialzizer()
- get_serializer_class
- get_serializer_context
- filter_queryset()
- paginate_queryset 调用paginator的paginate_queryset方法
- get_paginated_response 调用paginator的get_paginated_response方法