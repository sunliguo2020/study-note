### ViewSet

 **在ViewSet中，没有提供任何动作action方法，需要我们自己实现action方法。** 

 **ViewSet视图集类不再限制视图方法名只允许get()、post()等这种情况了，而是实现允许开发者根据自己的需要定义自定义方法名，例如 list() 、create() 等，然后经过路由中使用http和这些视图方法名进行绑定调用** 

```python
class ViewSet(ViewSetMixin, views.APIView):
    """
    The base ViewSet class does not provide any actions by default.
    """
    pass
```

### ViewSetMinxin

 **ViewSet主要通过继承ViewSetMixin来实现在调用as_view()时传入字典{“http请求”：“视图方法”}的映射处理工作，如
{‘get’:’list’，
‘post’:‘create’,
‘put’:‘update’,
‘delete’:‘destory’}，** 



```python
class ViewSetMixin:
    """
    This is the magic.

    Overrides `.as_view()` so that it takes an `actions` keyword that performs
    the binding of HTTP methods to actions on the Resource.

    For example, to create a concrete view binding the 'GET' and 'POST' methods
    to the 'list' and 'create' actions...

    view = MyViewSet.as_view({'get': 'list', 'post': 'create'})
    """

    @classonlymethod
    def as_view(cls, actions=None, **initkwargs):
       pass

        def view(request, *args, **kwargs):
     		pass

    def initialize_request(self, request, *args, **kwargs):
       pass

    def reverse_action(self, url_name, *args, **kwargs):
        pass

    @classmethod
    def get_extra_actions(cls):
		pass

    def get_extra_action_url_map(self):
        pass
```











### ModelViewSet

viewsets.py

````python
class ModelViewSet(mixins.CreateModelMixin,
                   mixins.RetrieveModelMixin,
                   mixins.UpdateModelMixin,
                   mixins.DestroyModelMixin,
                   mixins.ListModelMixin,
                   GenericViewSet):
    """
    A viewset that provides default `create()`, `retrieve()`, `update()`,
    `partial_update()`, `destroy()` and `list()` actions.
    """
    pass

````

```python
class GenericViewSet(ViewSetMixin, generics.GenericAPIView):
    """
    The GenericViewSet class does not provide any actions by default,
    but does include the base set of generic view behavior, such as
    the `get_object` and `get_queryset` methods.
    """
    pass

```

GenericAPIView

```python

class GenericAPIView(views.APIView):
    """
    Base class for all other generic views.
    """
  
    queryset = None
    serializer_class = None

    lookup_field = 'pk'
    lookup_url_kwarg = None

    # The filter backend classes to use for queryset filtering
    filter_backends = api_settings.DEFAULT_FILTER_BACKENDS

    # The style to use for queryset pagination.
    pagination_class = api_settings.DEFAULT_PAGINATION_CLASS

    def get_queryset(self):
            pass
    def get_object(self):
        pass

    def get_serializer(self, *args, **kwargs):
        pass

    def get_serializer_class(self):
        pass

    def get_serializer_context(self):
        pass

    def filter_queryset(self, queryset):
        pass

    @property
    def paginator(self):
        pass

    def paginate_queryset(self, queryset):
       pass
    def get_paginated_response(self, data):
        pass
```

