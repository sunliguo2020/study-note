# Django 在Django中对外键进行过滤

在本文中，我们将介绍在Django中如何对外键进行过滤。Django是一个功能强大的[Python](https://geek-docs.com/python/python-top-tutorials/1000100_python_index.html) Web框架，它提供了很多方便的工具来操作数据库。当我们的数据库模型中存在外键关联时，有时我们需要根据外键的值进行过滤查询，以获取我们需要的数据。



## 什么是外键？

在数据库中，外键表示两个表之间的关系。一个模型中的外键字段引用另一个模型的主键字段，用来建立关联关系。在Django的ORM中，我们可以通过ForeignKey字段来定义外键。



例如，假设我们有两个模型：`Author`和`Book`，其中`Book`模型有一个外键字段指向`Author`模型的主键。

```python
class Author(models.Model):
    name = models.CharField(max_length=100)

class Book(models.Model):
    title = models.CharField(max_length=100)
    author = models.ForeignKey(Author, on_delete=models.CASCADE)
```

在上面的例子中，`Book`模型中的`author`字段是一个外键字段，它建立了`Author`模型与`Book`模型之间的关联关系。

## 如何进行外键过滤？

在Django中，我们可以使用外键字段的名称后加`__`（双下划线）来对外键进行过滤。下面是一些常用的外键过滤操作。

#### 过滤一个外键对象

如果我们想要获取特定外键值的对象，可以使用`外键字段名__exact`进行过滤。例如，要获取作者名为”John”的所有书籍，可以使用以下代码：

```python
books = Book.objects.filter(author__name__exact="John")
```

#### 不区分大小写过滤

对于不区分大小写的过滤，可以使用`iexact`进行匹配。例如，要获取作者名为”john”的所有书籍，无论大小写，可以使用以下代码：

```python
books = Book.objects.filter(author__name__iexact="john")
```



#### 多个条件过滤

当我们需要使用多个条件进行过滤时，可以通过链式调用多个`filter`方法来实现。例如，要获取作者名为”John”且国籍是”USA”的所有书籍，可以使用以下代码：



```python
books = Book.objects.filter(author__name="John").filter(author__nationality="USA")
```

Python

Copy

还可以使用逗号分隔的方式，将多个条件放在一个`filter`方法中。例如：

```python
books = Book.objects.filter(author__name="John", author__nationality="USA")
```

Python

Copy

#### 使用外键对象的属性进行过滤

当我们想根据外键对象的属性进行过滤时，可以使用`外键字段名__属性名`的方式进行过滤。例如，要获取作者年龄大于30岁的所有书籍，可以使用以下代码：

```python
books = Book.objects.filter(author__age__gt=30)
```

Python

Copy

#### 使用外键对象的相关对象进行过滤

有时我们需要根据外键对象的相关对象进行过滤。我们可以使用`外键字段名__相关模型的字段名`的方式进行过滤。例如，要获取类型为”Science Fiction”的所有书籍，可以使用以下代码：

```python
books = Book.objects.filter(genre__name="Science Fiction")
```

Python

Copy

上面的例子中，`Book`模型中有一个名为`genre`的外键字段，它与`Genre`模型相关联。我们使用`genre__name`来获取`Genre`模型中`name`字段为”Science Fiction”的所有书籍。

## 示例

让我们通过一个简单的示例来演示如何使用外键进行过滤。

假设我们有以下的模型：



```python
class Category(models.Model):
    name = models.CharField(max_length=100)

class Product(models.Model):
    name = models.CharField(max_length=100)
    category = models.ForeignKey(Category, on_delete=models.CASCADE)
```

Python

Copy

现在，我们想获取某个类型为”Electronics”的所有产品，可以使用以下代码：

```python
products = Product.objects.filter(category__name="Electronics")
```

Python

Copy

这将返回类型为”Electronics”的所有产品对象。

## 总结

本文介绍了在Django中对外键进行过滤的方法。我们可以使用外键字段的名称后加`__`（双下划线）来进行过滤。我们可以根据外键对象的属性、相关对象的属性以及多个条件进行过滤。希望本文能够帮助你理解如何在Django中使用外键进行过滤。