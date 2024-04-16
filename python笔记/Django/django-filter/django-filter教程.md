### 1、安装

```python
pip install django-filter
```
### 2、加入到INSTALLED_APPS中

```python
INSTALL_APPS = [
    ...
    'django_filters'
]
```

### 3、快速使用

使用django-filter有点类似于django的forms类。创建filters.py,并自定义Filter类，其中Meta选项指定模型的某个字段来进行查询。

```python
import django_filters

class ArticleFilter(django_filters.FilterSet):

    class Meta:
        model = Article
        fields = ['title',]
```

现在我们需要编写视图views.py, 使用ArticleFilter类。由于filter是django自带的关键词，不能用作变量名，这里我们将ArticleFilter类的实例命名为f。每个f其实包含两个属性，f.form生成筛选表单，f.qs包含筛选结果集。

```python
from .models import Article,
from .filters import ArticleFilter


# Create your views here.
def article_search(request):
    f = ArticleFilter(request.GET, queryset=Article.objects.filter(status='p'))
    context = {'filter': f, }
    return render(request, 'blog/article_search.html', context)
```

模版文件

```html
{% extends "blog/base.html" %}
<h3>搜索文章</h3>
{% block content %}
    <form action="" method="get">
		{{ filter.form.as_p }}
        <input type="submit" />
    </form>
<ul>
{% for obj in filter.qs %}
     <li>{{ obj.title }}, 类别: {{ obj.category.name }}</li>
{% endfor %}
</ul>
{% endblock %}
```

### 4、精确查询 or 模糊查询

默认为精确查询，改为模糊查询

```python
class ArticleFilter(django_filters.FilterSet):
    class Meta:
        model = Article
        fields = {
            'title': ['icontains'],
            'category__name': ['icontains'],
            'pub_date': ['year__gt'],
		}
```

### 5、优化filter类

```python
class ArticleFilter(django_filters.FilterSet):
    q = django_filters.CharFilter(field_name='title',
									lookup_expr='icontains', label="关键词")
    category = django_filters.ModelChoiceFilter(field_name='category', 													queryset=Category.objects.all(),)
    pub_date__gte = django_filters.NumberFilter(field_name='pub_date',
										lookup_expr='year__gte', label="发表年份>=")

    class Meta:
        model = Article
        fields = {}
```

### 6、JSONField过滤

```python
class HisInformationFilter(django_filters.FilterSet):
    idcard = django_filters.CharFilter(field_name='idcard', label='身份证号', lookup_expr='icontains')

    class Meta:
        model = models.HisInformation
        fields = ['idcard', 'year', 'data']
        filter_overrides = {
            JSONField: {
                'filter_class': django_filters.CharFilter,  # 或者其他合适的过滤器类
                'extra': lambda f: {
                    'lookup_expr': 'icontains',  # 或者其他合适的查找表达式
                },
            },
        }
```

### 7、动态获取下拉列表框

 在 Django 中，`django_filters` 库允许你为 Django REST framework 或其他视图创建强大的过滤功能。`ChoiceFilter` 是 `django_filters` 中的一个过滤器，它允许用户从预定义的选项列表中选择一个值来过滤查询集。

如果你想根据数据库的内容动态生成 `ChoiceFilter` 的选项，你可以在定义过滤器时重写 `filterset_class` 的 `__init__` 方法，并在其中根据数据库查询来设置选项。

以下是一个例子，展示了如何根据数据库中某个字段的唯一值来动态生成 `ChoiceFilter` 的选项：

```python
import django_filters  
from django.db.models import QuerySet  
from .models import MyModel  
  
class MyModelFilter(django_filters.FilterSet):  
    my_choice_field = django_filters.ChoiceFilter(choices=(), label='My Choice Field')  
  
    def __init__(self, *args, **kwargs):  
        super().__init__(*args, **kwargs)  
        # 从数据库中获取唯一值，并设置给 ChoiceFilter  
        self.filters['my_choice_field'].extra.update({'choices': self._get_choices()})  
  
    def _get_choices(self) -> list:  
        # 获取数据库中的唯一值，并转换为选择项  
        unique_values = MyModel.objects.values_list('my_field',flat=True).distinct().order_by('my_field')  
        return [(value, str(value)) for value in unique_values]  
  
    class Meta:  
        model = MyModel  
        fields = ['my_choice_field']
```

在这个例子中，`MyModelFilter` 类定义了一个 `my_choice_field` 过滤器，它的选项在 `__init__` 方法中根据 `MyModel` 的 `my_field` 字段的唯一值动态设置。`_get_choices` 方法负责从数据库中获取这些值，并将它们转换为 `(value, label)` 格式的选项列表。

请注意，这个实现假设 `my_field` 的值可以直接用作选项的标签。如果需要使用不同的标签，你可以在 `_get_choices` 方法中进行相应的转换。

另外，这种方法可能在每次实例化 `MyModelFilter` 时都会执行数据库查询，这可能会影响性能。如果需要优化性能，可以考虑缓存选项或使用其他策略来减少数据库查询的次数。

最后，请确保在实例化 `MyModelFilter` 时，传递了正确的 `request` 和 `queryset` 参数，以便 `django_filters` 能够正确工作。

