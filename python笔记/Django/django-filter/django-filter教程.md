### 1、安装

```python
pip install django-filter
```
### 2、加入到INSTALLED_APPS中

```
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
    category = django_filters.ModelChoiceFilter(field_name='category', queryset=Category.objects.all(),
	)
    pub_date__gte = django_filters.NumberFilter(field_name='pub_date',
										lookup_expr='year__gte', label="发表年份>=")

    class Meta:
        model = Article
        fields = {}
```

