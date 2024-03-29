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

#### 作用：

它在APIView的基础上增加了**操作序列化器和数据库查询**的方法，作用是为Mixin扩展类提供方法支持。

实现的功能：

类属性：

- queryset			指明使用的数据查询集
- serializer_class     指明视图使用的序列化器类
- lookup_field          模型主键
- lookup_url_kwarg    
- pagination_class      分页类
- paginator pagination_class的实例   分页器

方法：

- get_queryset()
- get_object()     获取单条记录
- get_serialzizer()    获取序列化后的数据
- get_serializer_class
- get_serializer_context
- filter_queryset()
- paginate_queryset 调用paginator的paginate_queryset方法
- get_paginated_response 调用paginator的get_paginated_response方法

## mixin类

```python
"""
Basic building blocks for generic class based views.

We don't bind behaviour to http method handlers yet,
which allows mixin classes to be composed in interesting ways.
"""
from rest_framework import status
from rest_framework.response import Response
from rest_framework.settings import api_settings


class CreateModelMixin:
    """
    Create a model instance.
    """
    def create(self, request, *args, **kwargs):
        pass

    def perform_create(self, serializer):
        serializer.save()

    def get_success_headers(self, data):
        pass


class ListModelMixin:
    """
    List a queryset.
    """
    def list(self, request, *args, **kwargs):
        pass


class RetrieveModelMixin:
    """
    Retrieve a model instance.
    """
    def retrieve(self, request, *args, **kwargs):
        pass


class UpdateModelMixin:
    """
    Update a model instance.
    """
    def update(self, request, *args, **kwargs):
        pass

    def perform_update(self, serializer):
        pass

    def partial_update(self, request, *args, **kwargs):
        pass


class DestroyModelMixin:
    """
    Destroy a model instance.
    """
    def destroy(self, request, *args, **kwargs):
       pass

    def perform_destroy(self, instance):
        pass

```















## ViewSetMixin 

作用：重写了as_view()方法，可以更方便地绑定动作行为actions

```python
class ViewSetMixin:
	@classonlymethod
    def as_view(cls, actions=None, **initkwargs):
    	pass
	
```

