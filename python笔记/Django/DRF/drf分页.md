Django RestFramework 中只有继承以下类的情况下才可以使用分页

- viewsets.ModelViewSet
- generics.ListAPIView
- generic.ListCreateAPIView

RestFramework默认提供了三种分页方式

- PageNumberPagination普通分页器
  - ?page=3&size=10
- LimitOffsetPagination偏移分页器
  - ?limit=20&offset=100
- CursorPagination游标分页器
  - 

## 1、新建自定义分页类

```python
from rest_framework.pagination import PageNumberPagination

class CustomPagination(PageNumberPagination):
    page_size = 10# 每页显示的数量
    max_page_size = 5  # 最多设置的每页显示的数量
    page_size_query_param = 'size'  # 每页显示数量的参数名称
    page_query_param = 'page'  # 页码的参数名称

    def get_paginated_response(self, data):
        return Response({
            'code': 200,
            'msg': 'success',
            'data': {
                'current_page': self.page.number,
                'total_pages': self.page.paginator.num_pages,
                'total_count': self.page.paginator.count,
                'result': data
            }
        })
```

## 2、改造视图类

```python
from rest_framework import viewsets
from .mypage import MyPage
from .models import Goods
from .serializers import GoodsSerializer


class GoodsView(viewsets.ModelViewSet):
    queryset = Goods.objects.all()
    serializer_class = GoodsSerializer
    pagination_class = CustomPagination
```

或者在settings.py中配置

```
# drf 分页
REST_FRAMEWORK = {
    'DEFAULT_PAGINATION_CLASS': 'utils.CustomPagination.CustomPagination',
    'PAGE_SIZE': 10
}

```



DRF（Django REST framework）的分页功能是为了处理大量数据的展示问题。当数据库中有大量数据时，如果一次性将所有数据加载到内存中，会给服务器带来巨大的压力，甚至可能导致内存溢出。因此，分页功能允许用户每次只加载和显示一小部分数据，这样可以有效地减轻服务器的压力，并提高应用程序的性能。

在DRF中，分页可以通过两种方式实现：全局分页和局部分页。

1. 全局分页：在Django的配置文件（settings.py）中设置默认的分页类以及每页显示的数据条数。这样，所有的视图都会使用这个设置进行分页。

例如：

```python
REST_FRAMEWORK = {  
    'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.LimitOffsetPagination',  
    'PAGE_SIZE': 3  
}
```

在这个例子中，`PAGE_SIZE`被设置为3，这意味着每页将显示3条数据。

1. 局部分页：在特定的视图中使用分页类。这种方式允许你为不同的视图设置不同的分页方式。

例如，你可以在你的视图中使用`LimitOffsetPagination`类进行分页：

```python
from rest_framework.pagination import LimitOffsetPagination  
  
class MyView(APIView):  
    pagination_class = LimitOffsetPagination  
      
    def get(self, request, format=None):  
        # 你的业务逻辑  
        pass
```

在这个例子中，`MyView`视图将使用`LimitOffsetPagination`进行分页。

DRF还提供了其他的分页类，如`PageNumberPagination`和`CursorPagination`，你可以根据需求选择使用。

此外，你还可以自定义分页类以满足特定的需求。例如，你可以改变默认的页面大小，或者添加额外的分页参数等。

总的来说，DRF的分页功能提供了一种有效的方式来处理大量数据的展示问题，它可以提高应用程序的性能，并减少服务器的压力。