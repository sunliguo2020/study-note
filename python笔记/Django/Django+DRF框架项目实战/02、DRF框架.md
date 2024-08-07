## DRF框架

# 一、开发模式和RESTful

## 1、web应用开发模式

## 2、REESTful介绍

### 	2.1 RESTFul特点：

- 1、每个URI代表1种资源；
- 2、客户端使用GET、POST、PUT、DELETE 4个标识操作方式的动词对服务器资源进行操作
  - GET 用来获取资源	
  - POST 用来新建资源
  - PUT 用来更新资源（整体更新）
  - PATCH 用来更新资源（局部更新）
  - DELETE 用来删除资源

3、通过操作资源的表现形式来操作资源

4、资源的形式是XML或者JSON

5、客户端与服务器之间的交互在请求之间是无状态的，从客户端到服务端的每个请求都必须包含理解请求所必需的信息。

## 3、RESTful API设计风格

### 1、HTTP动词

对于资源的具体操作类型，由HTTP动词表示。常用的HTTP动词有下面四个（括号里是对应的SQL命令）。

- GET(SELECT)
- POST(CREATE)
- PUT(UPDATE)
- DELETE(DELETE)

### 2、url路径

- 路径尽量用名词表示，而不用动词
  - 推荐
    - http://aip.baidu.com/projects
    - http://api.baidu.com/envs
- 不管是单一资源还是所有资源，路径中名词尽量用复数



### 3、过滤参数

如果接口需要通过条件过滤返回结果，那么过滤的条件参数，应作为查询字符串参数传递。

- 例如：

```
?limit=10   返回指定记录的数量
?offset=10
?page=2&size=10
?sortby=name&order=asc
```



### 4、返回状态码



### 5、返回内容



# 二、DRF框架介绍

## 1、安装和使用

```python
pip install djangorestframework
```

注册到项目中

## 2、Django开发RESTful接口

- 1、定义模型类
- 2、定义路由
- 3、定义视图

## 3、DRF开发RESTful接口

- 1、定义模型类
- 2、定义序列化器
  - 作用：
    - 进行序列化操作，将ORM对象转换为json数据
    - 进行反序列化，将json转换为ORM对象
      - 进行反序列化操作的时候，会对json数据中的每个字段进行校验
- 3、定义路由
- 4、定义视图

# 三、序列化器

## 1、序列化器的定义

​	Django REST framework中的序列化器通过类来定义，必须继承自rest_framework.serializers.Serializer。

序列化器中的字段和模型类中的字段类型保持一致。

模型类如下：

```python
class UserInfo(models.Model):
    name = models.CharField(max_length=20, verbose_name='用户名')
    pwd = models.CharField(max_length=18, verbose_name='密码')
    email = models.EmailField(max_length=40, verbose_name='邮箱')
    age = models.IntegerField(verbose_name='年龄', default=18)

    def __str__(self):
        return self.name

    class Meta:
        db_table = "userinfo"
        verbose_name = '用户信息'

```



序列化器的定义：

```python

class UserInfoSerializer(serializers.Serializer):
    name = serializers.CharField(max_length=18)
    pwd = serializers.CharField(max_length=20)
    email = serializers.EmailField(max_length=40)
    age = serializers.IntegerField(min_value=0, max_value=150)

    def create(self, validated_data):
        """
        自定义一个序列化器保存数据的方法
        :param validated_data:
        :return:
        """
        UserInfo.objects.create(validated_data)
        return validated_data

    def update(self, instance, validated_data):
        instance.name = validated_data['name']
        instance.pwd = validated_data['pwd']
        instance.email = validated_data['email']
        instance.age = validated_data['age']

        instance.save()
        return instance
```



## 2、字段类型与选项介绍

## 3、序列化操作

##### 1、环境准备

1、安装

###### 	2、创建应用

###### 	3、修改setting中的配置

###### 	4、model.py中定义模型类

```python
class UerInfo(models.Model):
    name = models.CharField(max_length=20, verbose_name='用户名')
    pwd = models.CharField(max_length=18, verbose_name='密码')
    email = models.EmailField(max_length=40, verbose_name='邮箱')
    age = models.IntegerField(verbose_name='年龄', default=18)

    def __str__(self):
        return self.name

    class Meta:
        db_table = "userinfo"
        verbose_name = '用户信息'
```

###### 	5、定义序列化器	

- 在应用中新建文件serializer.py

- 在文件serializer.py中定义序列化器

  ```python
  
  from rest_framework import serializers
  
  
  class UserInfoSerializer(serializers.Serializer):
      name = serializers.CharField(max_length=18)
      pwd = serializers.CharField(max_length=20)
      email = serializers.EmailField(max_length=40)
      age = serializers.IntegerField(min_value=0, max_value=150)
  
  ```

  ###### 6、激活迁移文件

  ###### 7、练习数据准备

  ```python
  # 进入交互环境添加测试数据
  UserInfo.objects.create(name='张三',pwd='123435',email='1234@qq.com',age=10)
  UserInfo.objects.create(name='李四',pwd='123435',email='1234@qq.com',age=10)
  UserInfo.objects.create(name='王五',pwd='123435',email='1234@qq.com',age=10)
  ```

  

##### 2、序列化操作

- **序列化：将python对象--->转化为json格式的数据**

  定义好Serializer类后，如果要通过序列化器类进行序列化，需要先创建Serializer对象。

  Serializer参数为：

  ```python
  Serializer(instance=None,data={empty},**kwargs)
  ```

  1)用于序列化时，将模型对象传入instance参数

  2)用户反序列化时，将要被反序列化的数据传入data参数

  1、单个数据序列化

  ```python
  # 通过模型类查询一条用户信息
  obj = UserInfo.objects.first()
  # 使用查询到的用户信息，创建一个序列化对象
  ser = UserInfoSerializer(obj)
  # 
  ser.data
  {'name': '张三', 'pwd': '123435', 'email': '1234@qq.com', 'age': 10}
  
  ```

  2、查询集序列化

  ```python
  obj = UserInfo.objects.all()
  ser = UserInfoSerializer(obj,many=True)
  ser.data
  [OrderedDict([('name', '张三'), ('pwd', '123435'), ('email', '1234@qq.com'), ('age', 10)]), OrderedDict([('name', '李四'), ('pwd', '123435'), ('email', '1234@qq.com'), ('age', 10)]), OrderedDict([('name', '王五'), ('pwd', '123435'), ('email', '1234@qq.com'), ('age', 10)])]
  
  ```

  - 对多个数据进行序列化加参数：many=True

  3、将序列化的数据转换为json
  
  ```python
  
  from rest_framework.renderers import JSONRenderer
  # 查询用户是对象
  obj = UserInfo.objects.get(id=1)
  # 创建序列化器对象
  u = UserInfoSerializer(obj)
  # 将得到的字段，转换为json数据
  JSONRenerer().render(u.data)
  ```

##### 3、关联对象嵌套序列化

1、数据准备

​	定义模型类：

```python

class Addr(models.Model):
    user = models.ForeignKey("UserInfo",verbose_name='所属用户',on_delete=models.CASCADE)
    mobile = models.CharField(verbose_name='手机号',max_length=19)
    city = models.CharField(verbose_name='城市',max_length=20)
    info = models.CharField(verbose_name="详细地址",max_length=200)

    def __str__(self):
        return self.info
```

插入数据

```python
obj = UserInfo.objects.get(id=1)
Addr.objects.create(user=obj,mobile='18898789878',city='长沙',info='湖南长沙市阅览区')
<Addr: 湖南长沙市阅览区>
Addr.objects.create(user=obj,mobile='188987823278',city='长沙',info='湖南长沙撒旦发生发')
<Addr: 湖南长沙撒旦发生发>
```

查询：

```python
UserInfo.objects.get(id=1).addr_set
<django.db.models.fields.related_descriptors.create_reverse_many_to_one_manager.<locals>.RelatedManager object at 0x000001C95FCB4C40>

```



定义序列化器类

```python
class AddrSerializer(serializers.Serializer):
    mobile = serializers.CharField(max_length=18)
    city = serializers.CharField(max_length=20)
    info = serializers.CharField(max_length=200)

    # 关联字段序列化
    user = serializers.PrimaryKeyRelatedField()
```

2、关联字段序列化的方式

- 1、PrimaryKeyRelatedField

- 返回关联字段的id

- ```python
  user = serializers.PrimaryKeyRelatedField()
  
  ```

  2、StringRelatedFiled

  - 返回关联字段模型类__str__方法返回的内容

  - ```python
    user = serializers.StringRelatedField()
    ```
  

3、使用关联对象的序列化器

- 返回关联对象序列化器返回的所有字段
  
- ```python
    # 关联模型的序列化器
    user = UserInfoSeralizer()
    ```
  
- 4、SlugRelatedField

- 指定返回关联对象某个具体字段

- ```python
  user = seralizers.SlugRelatedField(read_only=True,slug_field = 'name')
  ```


## 4、反序列化操作

- 反序列化----->将json格式数据 转换为python对象

在进行反序列化操作时，会对对象数据进行验证，验证通过的情况下再进行保存

反序列化时，初始化序列化器对象，将要被反序列化的数据传入data参数

##### 1、数据验证

- a）校验数据
  - 调用is_valid()方法进行校验，验证成功后返回True，否则返回False

##### 2、常用校验字段说明



3、将序列化得到的数据转换为json

```python
from rest_framework.renderers import JSONRenderer
# 查询用户对象
obj = UserInfo.objects.get(id=1)
# 创建序列化对象
u = UserInfoSerializer(obj)
# 将得到的字段，转为json数据
JSONRenderer().render(u.data)
```

##### 3、序列化器保存数据

验证通过后，如需保存数据，直接调用序列化器对象的save方法即可，save方法会自动触发序列化器中对应的方法来保存数据

```python
#反序列化
ser = UserInfoSerializer(data=data)
#校验数据
ser.is_valid()
# 保存数据
ser.save()
```

注意点：

- 保存：save会调用序列化器中定义的create方法
- 更新：save会调用序列化器中的定义的update方法

## 5、模型序列化器

为了方便我们定义序列化器，DRF为我们提供了ModelSerializer模型类序列化器来帮助我们快速创建一个Serializer类。

ModelSerializer与常规的Serializer相同，但提供了：

- 基于模型类自动生成一些列字段
- 基于模型类自动为Serializer生成验证器validators ，比如unique_together
- **包含默认的create()和update()的实现**

##### 1、模型序列化器的使用

- 定义模型化序列化器类，直接继承于serializers.ModelSerializer即可

  ```python
  class UserInfoSerializer(serializers.ModelSerializer):
      class Meta:
         model = UserInfo
         fields = "__all__"
  ```
  
  -指定模型类和需要序列化的字段
  
  - model指明参照哪个模型类
  - fields指明模型类的哪些字段生成

##### 2、指定字段

1、fields

- fields =“____all____" 代表模型类中所有字段都进行序列化

2、exclude 使用exclude可以明确排除哪些字段不参与序列化

3、read_only_fields 指明只读的字段（只参与序列化，不参与反序列化)

##### 3、修改字段的参数选项

- 使用extra_kwargs 参数为ModelSerializer添加或者修改原有的选项参数 反序列化校验规则 

  - 通过字段名指定字段对应的参数和值

  - ```python
    class UserInfoSerializer(serializers.ModelSerializer):
        class Meta:
            model = UserInfo
            fields = "__all__"
            extra_kwargs = {
                'pwd': {'min_value': 0,
                        'required': True},
            }
    
    ```

    

## 6、序列化器保存数据案例

- 前提是序列化模型类要是实现create方法和update方法

- 使用序列化器新增数据：

- ```python
  user1 = {'id': 1, 'name': 'sunliguo', 'pwd': '123435', 'email': '1234@qq.com', 'age': 10}
  ser = UserInfoSerializer(data=user1)
  # 校验数据
  ser.is_valid()
  # 保存数据
  ser.save()
  ```

使用序列化器修改数据：

```python
user = UserInfo.objects.get(id=1)
user1 = {'id': 1, 'name': 'sunliguo', 'pwd': '123435', 'email': '1234@qq.com', 'age': 10}
#创建序列化器
ser = UserInfoSerializer(instance=user,data=user1)
# 校验数据
ser.is_valid()
# 保存数据
ser.save()
```



## 7、利用序列化器实现增删改查的接口

视图

```python

def user_list(request):
    """
    get方法请求：获取用户列表
    post方法请求：添加用户信息
    :param request:
    :return:
    """
    if request.method == "GET":
        # 获取用户信息列表
        users = UserInfo.objects.all()
        # 创建序列化对象
        ser = UserInfoSerializer(users, many=True)
        result = {
            'data': ser.data,
            'code': 200,
            "message": "OK"
        }
        return JsonResponse(result)
    elif request.method == 'POST':
        params = JSONParser().parse(request)
        # 创建序列化器
        ser = UserInfoSerializer(data=params)
        # 校验请求数据
        if ser.is_valid():
            # 校验通过，则添加数据到数据
            ser.save()
            return JsonResponse({'code': 201, 'data': ser.data, "message": 'OK'})
        else:
            return JsonResponse({'code': 400, 'message': ser.errors})

    else:
        return JsonResponse({'code': 405, 'message': f"不支持该请求{request.method}"})


def user_detail(request, id):
    """
    GET:获取单个用户信息
    PUT：修改单个用户信息
    DELETE:删除用户信息
    :param request:
    :param id:
    :return:
    """
    try:
        obj = UserInfo.objects.get(id=id)
    except Exception as e:
        return HttpResponse('404 访问资源不存在', status=status.HTTP_404_NOT_FOUND)
    if request.method == 'GET':
        ser = UserInfoSerializer(obj)
        return JsonResponse({'code': 200, "data": ser.data, 'message': "OK"})
    elif request.method == "PUT":
        # 修改单个用户资源

        # ser = UserInfoSerializer(instance=obj, data=json.loads(request.body.decode('utf-8')))

        params = JSONParser().parse(request)
        ser = UserInfoSerializer(instance=obj, data=params)
        if ser.is_valid():
            ser.save()
            return JsonResponse({'code': 200, "data": ser.validated_data, "message": "OK"})
        else:
            return JsonResponse({'code': 400, 'message': ser.errors})
    elif request.method == 'DELETE':
        obj.delete()
        return JsonResponse({}, status=status.HTTP_204_NO_CONTENT)
    else:
        return JsonResponse({'code': 405, 'message': f"不支持该请求{request.method}"},
                            status=status.HTTP_405_METHOD_NOT_ALLOWED)

```

路由：

```python
   path('users/', views.user_list),
    re_path(r'users/(.+?)/', views.user_detail),
```



## 8、自定义验证方法

DRF支持自定义序列化器的校验方法：

- 定义校验方法

  - 验证方法名的规范：validate_字段名

    ```python
    class UserInfoSerializer(serializers.Serializer):
        def validate_pwd(self,value):
            """校验逻辑"""
    ```

- 通过validators字段指定验证函数



```python
  def leng_validate(value):
      if not(10<len(value)<20):
          raise serializers.ValidationError('字段的长度不在10-20之间')
       
  class UserInfoSerializer(serializers.Serializer):
      pwd = serializers.CharField(validators=length_validate)
      
        
```



# 三、请求和响应对象

## 1、DRF定义视图函数

案例：
```python

from rest_framework.decorators import api_view
from rest_framework.views import APIView
from rest_framework.response import Response

@api_view(['GET','POST'])
def user_list(request):
    return Response(data={'message':"OK"})

# Django 的request获取请求参数

# request.GET	#获取get请求传递的查询参数
# request.POST   #获取post请求传递的表单参数

# put patch post请求传递到请求体参数（json格式），Django中没有提供直接获取的方法
params = request.body.decode()
import json
params = json.loads(params)

DRF中的request对象：
1、对应查询参数（拼接在url后面的参数）的获取：
	request.query_params
 2、表单参数、json
	request.data

```

## 2、DRF的Request对象

REST framework传入视图的request对象不再是Django默认的HttpRequest对象，而是REST framework提供的扩展了HttpRequest类的Request类的对象。无论前端发送的哪种格式的数据，我们都可以以统一的方式读取数据。

##### 	1、request.data属性

- request.data获取请求体数据。
  - 支持POST PUT PATCH方法传递的请求体参数
  - 不仅支持表单类型数据，也支持JSON数据，还支持文件数据的获取

##### 2、request.query_params属性

request.query_params获取查询字符串参数的，Django的request.GET的作用一样



## 3、DRF的Response对象

rest_framework.response.Response

REST framework提供了相应类Response，使用该类构造相应对象时，相应的具体数据内容会被转换（render渲染）成符合前端需求的类型。

```python
Response(data,status=None,template_name=None,headers=None,content_type=None)
```

data不能是复杂结构的数据，如Django的模型类对象，对于这样的数据我们可以使用Serializer序列化器序列化处理后（转为Python字典类型）再传递给data参数。

##### 1、Response参数说明

- data:为响应准备的序列化处理后的数据；
- status：状态码，默认为200；
- template_name:模板名称，如果使用HTMLRenderer时需指明。
- headers：用于存放响应头信息的字典；
- content_type:响应数据的Content-Type，通常此参数无需传递，REST framework会根据前端所需类型数据来设置该参数

## 4、响应状态码

在视图中使用数字HTTP状态代码并不总是能带来明显的阅读效果，而且如果您输入了错误代码，很容易察觉不到。REST框架为每个状态代码（如模块中）提供更明确的标识符。HTTP_400_BAD_REQUEST

```python
from rest_framework import status
status.HTTP_200_OK
```



## 5、API视图的装饰器

REST框架提供了两个可用于编写API视图的装饰器

- 用于处理基于函数的装饰器  @api_view

```
Decorator that converts a function-based view into an APIView subclass.Takes a list of allowed methods for the view as an argument.
将基于函数的视图转换为 APIView 子类的装饰器。将视图允许的方法列表作为参数。

```



- 用于处理基于类的视图的类 。APIView

下面我们通过@api_view这个装饰器来实现增删改查接口

##### 1、使用DRF视图函数完成增删查改

```python
from rest_framework import status
from rest_framework.decorators import api_view
from rest_framework.response import Response

from .models import UserInfo
from .serializers import UserInfoSerializer


# Create your views here.

class UserListView(APIView):
    def get(self, request, format=None):
        pass

    def post(self, request, format=None):
        pass


@api_view(['GET', 'POST'])
def user_list(request):
    """
    get方法请求：获取用户列表
    post方法请求：添加用户信息
    :param request:
    :return:
    """
    if request.method == "GET":
        # 获取用户信息列表
        users = UserInfo.objects.all()
        # 创建序列化对象
        ser = UserInfoSerializer(users, many=True)
        result = {
            'data': ser.data,
            'code': 200,
            "message": "OK"
        }
        return Response(result, status=status.HTTP_200_OK)
    elif request.method == 'POST':

        # 创建序列化器
        ser = UserInfoSerializer(data=request.data)
        # 校验请求数据
        if ser.is_valid():
            # 校验通过，则添加数据到数据
            ser.save()
            return Response({'code': 201, 'data': ser.data, "message": 'OK'})
        else:
            return Response({'code': 400, 'message': ser.errors}, status=status.HTTP_400_BAD_REQUEST)


@api_view(['GET', 'PUT', 'DELETE'])
def user_detail(request, id):
    """
    GET:获取单个用户信息
    PUT：修改单个用户信息
    DELETE:删除用户信息
    :param request:
    :param id: 操作资源的id
    :return:
    """
    try:
        obj = UserInfo.objects.get(id=id)
    except Exception as e:
        return Response({"code": 404, "message": "404,访问的资源不存在!"}, status=status.HTTP_404_NOT_FOUND)

    if request.method == 'GET':
        ser = UserInfoSerializer(obj)
        return Response({'code': 200, "data": ser.data, 'message': "OK"}, status=status.HTTP_200_OK)
    elif request.method == "PUT":
        # 修改单个用户资源
        # ser = UserInfoSerializer(instance=obj, data=json.loads(request.body.decode('utf-8')))

        ser = UserInfoSerializer(instance=obj, data=request.data)
        if ser.is_valid():
            ser.save()
            return Response({'code': 200, "data": ser.validated_data, "message": "OK"}, status=status.HTTP_200_OK)
        else:
            return Response({'code': 400, 'message': ser.errors}, status=status.HTTP_400_BAD_REQUEST)
    elif request.method == 'DELETE':
        obj.delete()
        return Response({}, status=status.HTTP_204_NO_CONTENT)



```

## 6、使用DRF给url添加后缀

1、修改视图函数

在视图函数后面添加参数format，并设置默认值为空

```python
@api_view(['GET','POST'])
def user_list(request,format=None):
    pass
@api_view(['GET','PUT','DELETE'])
def user_detail(request,id,format=None):
    pass
```

2、修改路由配置

```python
from django.urls import path
from . import views
from rest_framework.urlpatterns import format_suffix_patterns
urlpatterns = [
    path('users/',views.user_list),
    path('users/<int:id>/',view.user_detail)
]
urlpatterns = format_suffix_patterns(urlpatterns)
```

3、效果

```python

# 访问： Http://127.0.0.1:8000/app1/user.json 返回json数据
# 访问 http://127.0.0.1:8000/app1/users.api 访问DRF自带的接口调试页面
```

## 7、类视图APIView

APIView是REST framework提供的所有视图的基类，继承自Django的View父类。支持认证、限流、授权等功能。

> rest_framework.views.APIView



1、APIView与View的区别：

- 传入到视图方法中的是REST framework的Request对象,而不是Django的HttpRequest对象。
- 视图方法可以返回REST framework的Response对象，视图会为响应数据设置（render）符合前端要求的格式；
- 任何APIException异常都会被捕获到，并且处理成合适的响应信息。
- 扩展了身份认证、权限检查、流量控制这个三个功能

2、扩展的功能

- authentication_classes: 列表或元组 身份认证 
- permission classes ：列表或元组 权限检查
- throttle_classes: 列表或元组  限流

3、基于APIView实现增删查改

```python
class UserListView(APIView):
    def get(self, request, format=None):
        # 获取用户信息列表
        users = UserInfo.objects.all()
        # 创建序列化对象
        ser = UserInfoSerializer(users, many=True)
        result = {
            'data': ser.data,
            'code': 200,
            "message": "OK"
        }
        return Response(result, status=status.HTTP_200_OK)

    def post(self, request, format=None):
        # 创建序列化器
        print(request.data)
        ser = UserInfoSerializer(data=request.data)
        # 校验请求数据
        if ser.is_valid():
            # 校验通过，则添加数据到数据
            ser.save()
            return Response({'code': 201, 'data': ser.data, "message": 'OK'})
        else:
            return Response({'code': 400, 'message': ser.errors}, status=status.HTTP_400_BAD_REQUEST)


class UserDetailView(APIView):
    def get_object(self, id):
        try:
            return UserInfo.objects.get(id=id)
        except Exception as e:
            raise Http404()

    def get(self, request, id, format=None):
        obj = self.get_object(id)
        ser = UserInfoSerializer(obj)
        return Response({'code': 200, "data": ser.data, 'message': "OK"}, status=status.HTTP_200_OK)

    def put(self, request, id, format=None):
        obj = self.get_object(id)
        # 修改单个用户资源
        ser = UserInfoSerializer(instance=obj, data=request.data)
        if ser.is_valid():
            ser.save()
            return Response({'code': 200, "data": ser.validated_data, "message": "OK"}, status=status.HTTP_200_OK)
        else:
            return Response({'code': 400, 'message': ser.errors}, status=status.HTTP_400_BAD_REQUEST)

    def delete(self, request, id, format=None):
        obj = self.get_object(id)
        obj.delete()
        return Response({}, status=status.HTTP_204_NO_CONTENT)

```





# 四、视图集和路由

## 4.1、GenericAPIView通用视图

### 4.1.1 什么是GenericAPIView

它在APIView类的基础上增加了操作序列化器和数据库查询的方法，作用是为Mixin扩展类提供方法支持。

继承自APIView，拥有APIView所有的特性（认证、限流、授权），还支持搜索、分页、排序等功能。

主要增加了操作序列化器和数据库查询的方法，作用是为下面Minxin扩展类的执行提供方法支持。通常在使用时，可搭配一个或多个Mixin扩展类。

rest_framework.generics.GenericAPIView继承自APIView，增加了对于列表视图的详情视图可能用到的通用支持方法。

### 4.1.3 GenericAPIView类的原理

1、GerericAPIView类的属性和方法

| 属性和方法             | 说明                                        |
| ---------------------- | ------------------------------------------- |
| queryset               | 指明使用的数据查询集                        |
| serializer_class       | 指明视图使用的序列化器                      |
| loopup_field           | 指明模型主键                                |
| get_queryset           | 提供方法，以获取request请求封装完毕的结果集 |
| get_object             | 获取单条数据                                |
| get_serializer         | 获取序列化后的数据                          |
| get_serializer_class   | 获取需要序列化的model类                     |
| get_serializer_context | 获取序列化的数据，定义了某种格式的字典      |
| Paginator              | 分页器                                      |



```python
# You'll need to either set these attributes,
# or override `get_queryset()`/`get_serializer_class()`.
# If you are overriding a view method, it is important that you call
# `get_queryset()` instead of accessing the `queryset` property directly,
# as `queryset` will get evaluated only once, and those results are cached# for all subsequent requests.

您需要设置这些属性，或覆盖“get_queryset（）”get_serializer_class（）”。如果要重写视图方法，请务必调用“get_queryset（）”而不是直接访问“queryset”属性，因为“queryset”将仅被计算一次，并且这些结果将缓存用于所有后续请求。
```

如果你想使用GenericAPIview，你需要从如下二种选择其一：

1. 在视图类中设置如下属性 (常用)

   `queryset`、`serializer_class`

2. 重写GenericAPIview类的`get_queryset()`/`get_serializer_class()`方法

如果你重写了一个视图方法，那么重要的是 你应该调用get_queryset() 而不是直接的访问`queryset`属性。
因为`queryset`将只被设置一次，并且为了后续到来的所有请求，这个结果会被缓存。

**总而言之，不要直接访问`queryset`、`serializer_class`属性，而是使用GenericAPIview提供的各种方法获取。**

需要设置queryset 和serializer_class 属性，或者重写get_queryset()和get_serializer_class()

1、扩展的类属性

- queryset :指定当前视图使用的查询集
- serializer_class:指明类视图使用的序列化器

2、扩展的方法：

- self.queryset():获取查询集
- self.serializer():获取序列化器
- self.get_serializer_class(self) :返回序列化器类，默认返回serializer_class
- self.get_object():获取指定的单一对象

3、扩展功能

- pagination_class:指明分页控制类
- filter_backends:数据过滤&排序
- 指定单一数据获取的参数字段：
  - lookup_field 查询单一数据库对象时使用的条件字段，默认为‘pk’
  - lookup_url_kwarg 查询单一数据时URL中的参数关键字名称，默认与lookup_field相同

## 4.2、扩展视图类

扩展类提供了几种后端视图（对数据资源进行增删查改）处理流程的实现，如果需要编写的视图属于这五种，则视图可以通过继承相应的扩展类来复用代码，减少自己编写的代码量。

这五个扩展类需要搭配GenericAPIView父类，因为5个扩展类的实现需要调用GenericAPIView提供的**序列化器与数据库查询**的方法。

### 1、基本扩展类：

DRF框架包含5类Mixin

| 类                 | 说明                                                  | 请求方法  |
| ------------------ | ----------------------------------------------------- | --------- |
| ListModelMixin     | 以列表方式返回一个QuerySet列表，提供list()方法        | GET       |
| CreateModelMixin   | 创建一个实例，提供create()方法、perform_create()方法  | POST      |
| RetrieveModelMixin | 返回一个具体的实例，提供retrieve()方法                | GET       |
| UpdateModelMixin   | 对某个实例进行更新，提供pdate()、perform_update()方法 | PUT PATCH |
| DestoryModelMixin  | 删除某个实例，提供delete()、perform_destory()方法     | DELETE    |



- ListModelMinxin:
  - 列表视图扩展类，提供list(request,*args,**kwargs)方法快速实现列表视图
  
  - 状态码：200
  
  - 该Mixin的list方法会对数据进行过滤和分页。
  
  - 源码
  
    - ```python
      class ListModelMixin(object):
          """
          List a queryset.
          """
          def list(self, request, *args, **kwargs):
              # 过滤
              queryset = self.filter_queryset(self.get_queryset())
              # 分页
              page = self.paginate_queryset(queryset)
              if page is not None:
                  serializer = self.get_serializer(page, many=True)
                  return self.get_paginated_response(serializer.data)
              # 序列化
              serializer = self.get_serializer(queryset, many=True)
              return Response(serializer.data)
      
      ```
  
  - 举例：
  
    - ```python
      from rest_framework.mixins import ListModelMixin
      
      class BookListView(ListModelMixin, GenericAPIView):
          queryset = BookInfo.objects.all()
          serializer_class = BookInfoSerializer
      
          def get(self, request):
              return self.list(request)
      
      ```
  
    - 
- CreateModelMixin：
  - 创建视图扩展类，提供create(request,*args,**kwargs)方法快速实现创建资源的视图
  
  - 成功返回201状态码，如果序列化器对前端发送的数据验证失败，返回400错误。
  
  - 源码
  
    - ```python
      class CreateModelMixin(object):
          """
          Create a model instance.
          """
          def create(self, request, *args, **kwargs):
              # 获取序列化器
              serializer = self.get_serializer(data=request.data)
              # 验证
              serializer.is_valid(raise_exception=True)
              # 保存
              self.perform_create(serializer)
              headers = self.get_success_headers(serializer.data)
              return Response(serializer.data, status=status.HTTP_201_CREATED, headers=headers)
      
          def perform_create(self, serializer):
              serializer.save()
      
          def get_success_headers(self, data):
              try:
                  return {'Location': str(data[api_settings.URL_FIELD_NAME])}
              except (TypeError, KeyError):
                  return {}
      
      ```
  
    - 
- RetrieveModelMixin：获取单一数据
  - 详情视图扩展类，提供retrieve方法，可以快速实现返回一个存在的数据对象。
  - 如果成功，返回200，否则返回404
- UpdateModelMixin：更新数据
  - 更新视图扩展类，提供update方法和partial_update方法，可以快速实现更新一个存在的数据对象。
  - 成功返回200，序列化器校验数据失败时，返回400错误。
- DestroyModelMixin：
  - 删除视图扩展类，提供destroy方法，可以快速实现删除一个存在的数据对象。
  - 成功返回204，不存在返回404。

### 2、视图扩展类   子类视图

1、CreateAPIView

- 继承自：GenericAPIView、CreateModelMixin
- 提供post方法

2、ListAPIView

- 继承自GenericAPIView、ListModelMixin
- 提供get方法

3、RetireveAPIView

- 继承自：GenericAPIView，RetrieveModelMixin
- 提供get方法

4、DestoryAPIView

- 继承自：GenericAPIView、DestoryModelMixin
- 提供delete方法

5、UpdateAPIView

- 继承自：GenericAPIView、UpdateModelMixin
- 提供put和patch方法

6、RetrieveUpdateAPIView

- 提供 get、put、patch方法
- 继承自： GenericAPIView、RetrieveModelMixin、UpdateModelMixin

7、RetrieveUpdateDestoryAPIView

- **提供 get、put、patch、delete方法**
- 继承自：GenericAPIView、RetrieveModelMixin、UpdateModelMixin、DestoryModelMixin
  

## 4.3、视图集

常见视图集父类

ViewSet

继承自APIView与ViewSetMixin，作用也与APIView基本类似，提供了身份认证、权限校验、流量管理等。

ViewSet主要通过继承ViewSetMixin来实现在调用as_view()时传入字典（如：{'get'：'list'}的映射处理工作。

在ViewSet中，没有提供任何动作action方法，需要我们自己实现action方法。

1、视图集的使用

ViewSet视图集类不再实现get()、post()等方法，而是实现action如list()、create()等。将一系列逻辑相关的动作放到一个类中：

- list()提供一组数据
- retrieve()提供单个数据
- create()创建数据
- update()保存数据
- destory()删除数据

注意点：

在使用视图集的时候，在配置路由的时候，用自行指定请求方法和处理的视图函数。

```
urlpatterns = [
path(r'^books/$',xxViewSet.as_view({'get':list})),
path(r'^books/<int:id>/$',xxxInfoViewSet.as_view({'get':'retrieve'}))
]
```

2、action属性

视图集只在使用as_view()方法的时候，才会将action动作与具体请求方式对应上。

3、常用视图集类

1）ViewSet

继承自APIView，作用也与APIView基本雷士，提供了身份认证、权限校验、流量管理等。

在ViewSet中，没有提供任何动作action方法，需要我们自己实现action方法

源码：

```python
class ViewSet(ViewSetMixin, views.APIView):
    """
    The base ViewSet class does not provide any actions by default.
    """
    pass

```

ViewSetMixin

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
```





2）GenericViewSet

继承自GenericAPIView，作用也与GenericAPIView类似，提供了get_object、get_queryset等方法便于列表视图与详情信息视图的开发。

源码

```python
class GenericViewSet(ViewSetMixin, generics.GenericAPIView):
    """
    The GenericViewSet class does not provide any actions by default,
    but does include the base set of generic view behavior, such as
    the `get_object` and `get_queryset` methods.
    """
    pass
```



3）ModelViewSet

继承自GenericAPIView，同时包括了ListModelMixin、RetrieveModelMixin、CreateModelMixin、UpdateModelMinxin、DestoryModelMinxin。

源码：

```python
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
```



4）ReadOnlyModelViewSet

继承自GenericAPIView，同时包括了ListModelMixin、RetrieveModelMixin。

4、路由

对于视图集ViewSet，我们除了可以自己手动指明请求方式与动作action之间的对应关系外，还可以使用

## 4.4 总结

```
# 两个视图基类 
1.APIView       
2.GenericAPIView
APIView：       renderer_classes响应格式类 parser_classes请求解析类    跟数据库解耦合
GenericAPIView：queryset数据集 serializer_class序列化类                跟数据库耦合

# 5个视图扩展类 (提供方法)
ListModelMixin      -->  list      -->  查询所有
RetrieveModelMixin  -->  retrieve  -->  查询一个
CreateModelMixin    -->  create    -->  新增一个
UpdateModelMixin    -->  update    -->  修改一个
DestroyModelMixin   -->  destroy   -->  删除一个

# 9个视图子类 
继承关系公式： 视图子类 = n * 视图扩展类 + GenericAPIView 

# 示例：
ListAPIView     =  ListModelMixin     + GenericAPIView 
RetrieveAPIView =  RetrieveModelMixin + GenericAPIView 
CreateAPIView   =  CreateModelMixin   + GenericAPIView 
DestroyAPIView	= DestroyModelMixin	  + GenericAPIView
UpdateAPIView
ListCreateAPIView
RetrieveUpdateAPIView
RetrieveDestroyAPIView = RetrieveModelMixin + DestroyModelMixin + GenericAPIView 
RetrieveUpdateDestroyAPIView = RetrieveModelMixin + UpdateModelMixin + DestroyModelMixin + GenericAPIView

'''
总结：9个视图子类都继承GenericAPIView
'''
```

```

# from rest_framework.viewsets下有这几个类：

ViewSetMixin：魔法类，重写了as_view，只要继承他，以后路由写法变成了映射方法
ModelViewSet: 5个视图扩展类 + ViewSetMixin(魔法类) + GenericAPIView
ReadOnlyModelViewSet: 2个视图扩展类 + ViewSetMixin(魔法类) + GenericAPIView   只读的两个
ViewSet：ViewSetMixin(魔法类)  + APIView
GenericViewSet：ViewSetMixin(魔法类) + GenericAPIView

# 重点
	以后，你想继承APIView，但是想变路由写法【视图类中方法名任意命名】，要继承ViewSet
    以后，你想继承GenericAPIView，但是想变路由写法【视图类中方法名任意命名】，要继承GenericViewSet
    
# 总结
只要想变路由，就要继承ViewSetMixin，但是ViewSetMixin不是CBV视图类，他没有list，create等方法，所以要配合APIView, GenericAPIView一起使用，所以会出现ViewSet,GenerucViewSet，帮助我们继承好了。
ViewSet：       ViewSetMixin(魔法类)  + APIView
GenericViewSet：ViewSetMixin(魔法类)  + GenericAPIView

```

###  视图层大总结

```
# 1. 两个视图基类
	-APIView，GenericAPIView
# 2. 5个视图扩展类，不是视图类，必须配合GenericAPIView

# 3. 9个视图子类，是视图类，只需要继承其中某一个即可

# 4. 视图集 
	-ModelViewSet：路由写法变了，只需要写两行，5个接口都有了
    -ReadOnlyModelViewSet：路由写法变了，只需要写两行，2个只读接口都有了
    -ViewSetMixin：不是视图类，魔法，重写了as_view,路由写法变了，变成映射了
    	views.BookView.as_view({'get': 'list', 'post': 'create'})
    -ViewSet：ViewSetMixin+ APIView
	-GenericViewSet：ViewSetMixin+ GenericAPIView

# 举例子：发送短信接口，视图类叫SendView，方法叫send_sms，路由配置变了
	get--->send_sms
	class SendView(ViewSet):
        def send_sms(self,request):
            
```



# 五、其他功能

#### 1、认证&权限

#### 2、限流

#### 3、过滤

对于列表数据可能需要根据字段进行过滤，我们可以通过添加django-filter扩展来增强支持。

```python
pip install django-filter
```

在配置文件中增加过滤后端的设置：

```python
# 注册到应用
INSTALLED_APPS = [
   ...
    'django_filters',
]

# 配置DRF过滤器
REST_FRAMEWORK = {

    # 配置DRF过滤器
    'DEFAULT_FILTER_BACKENDS':['django_filters.rest_framework.DjangoFilterBackend']
}
```

在视图中添加filterset_fields属性，指定可以过滤的字段

```python
class StudentView(ListAPIView):
	queryset = BookInfo.objects.all()
	serializer_class = BookInfoSerializer
	filterset_fields = ('age',)
```



#### 4、排序

对于列表数据，REST framework提供了OrderingFilter过滤器来帮助我们快速指明数据按照指定字段进行排序。

- filter_backends:指定排序过滤器。
- ordering_fields:指定排序的可选字段。

REST framework会在请求的查询字符串参数中检查是否包含了ordering参数，如果包含了ordering参数，则按照ordering参数指明的排序字段对数据集进行排序。

要实现排序，则需要配置filters.OrderingFilter和ordering_fields排序字段。其中，ordering_fields排序字段等于要排序的字段元组。

```python
class UsersListCreateAPIView(ListCreateAPIView):
    queryset = models.Users.objects.all()
    serializer_class = UserSerializer
    
    # 排序
    filter_backends = (DjangoFilterBackend, filters.OrderingFilter)
    ordering_fields = ('id', 'nickname')
```



#### 5、分页

REST framework提供了分页的支持。

##### 1、全局配置

在配置文件中配置全局的分页方式：

```python
REST_FRAMEWORK = {
   
    'DEFAULT_PAGINATION_CLASS': 'rest_framework.pagination.PageNumberPagination', 
    'PAGE_SIZE': 10,   
}
```

##### 2、局部配置

在不同的视图中可以通过pagination_class属性来指定不同的分页器。

- 自定义分页器

  自定义个继承PageNumberPagination的类型，在子类中通过属性定义分页器的数据：

  - page_size 每页默认的数据条数
  - page_query_param 前端发送的页数的关键字名，默认为“page”
  - page_size_query_param 前端发送的每页数目的关键字名，默认为None
  - max_page_size 每页最多的数据条数

  ```python
  class CustomPagination(PageNumberPagination):
      """
      自定义分页类
      """
      page_size = 10  # 每页显示的数目
      page_query_param = 'page'  # 页码的参数名称
      page_size_query_param = 'size'  # 每页显示数量的参数名称
      max_page_size = 50  # 每页最多显示的数目
  
      def get_paginated_response(self, data):
          """
          自定义分页返回格式
          """
          return Response({
              'code': 200,
              'msg': 'success',
              'data': data,
              'current_page': self.page.number,
              'next_page': self.get_next_link(),
              'previous_page': self.get_previous_link(),
              'page_size': self.page_size,
              'total_pages': self.page.paginator.num_pages,
              'total_count': self.page.paginator.count,
  
          }, status=status.HTTP_200_OK)
  
  ```

  

#### 6、异常处理

REST framework提供了异常处理，如果没有自定义默认会采用默认的处理方法方式

```python
REST_FRAMEWORK = {
    # REST_FRAMEWORK 默认的异常处理方法
    'EXCEPTION_HANDLER':'rest_framework.views.exception_handler'
}
```

##### 1、自定义异常处理的方法

- 定义异常处理的方法

#### 7、文件上传

#### 8、接口文档

REST framework通过第三方库可以帮助我们生成网页版的接口文档，自动接口文档生成的继承自APIView及其子类的视图。

##### 1、安装依赖

REST framework生成接口文档需要coreapi库的支持。

```python
pip install coreapi
```

##### 2、设置接口文档访问路径

- 在项目路由中添加接口文档的路由，配置如下：

```python
from rest_framework.documentation import include_docs_urls

urlpatterns = [
    re_path(r'^docs/', include_docs_urls(title='接口文档')),]
```

- 加上配置

```python
REST_FRAMEWORK = {
 
    #  添加coreapi框架 否则会提示：AttributeError: 'AutoSchema' object has no attribute 'get_link'
    'DEFAULT_SCHEMA_CLASS': 'rest_framework.schemas.coreapi.AutoSchema',
}
```





# 六、ajax跨域

​	1、安装第三方库django-cors-headers

```python
pip install django-cors-headers
```

2. 在settings.py 中 INSTALLED_APPS 下 添加 一个 corsheaders 
```
INSTALLED_APPS = [
    ....
    'corsheaders',
]

```
3. 在settings.py 中 Midddleware 中，添加对应的中间件
```python
MIDDLEWARE = [ 
    ...
    'corsheaders.middleware.CorsMiddleware',
    'django.middleware.common.CommonMiddleware',
    ...
]
```
4. 在settings.py 中设置跨域的基本参数
- CORS_ORIGIN_ALLOW_ALL ：默认是False, 如果为 True， 则允许所有网站跨域


# 七、DRF JWT

### 1、token鉴权和JWT介绍

### 2、simpleJWT

1、安装djangorestframework-simplejwt

```python
pip install djangorestframework-simplejwt
```

2、settings.py中添加配置

- 注册到应用中

```
INSTALLED_APPS = [
   ...
    'rest_framework_simplejwt',
]
```

- DRF配置鉴权方式

  ```python
  # DRF的配置鉴权方式
  REST_FRAMEWORK = {
      # 配置登录鉴权方式
      'DEFAULT_AUTHENTICATION_CLASSES': (
          'rest_framework_simplejwt.authentication.JWTAuthentication',
          'rest_framework.authentication.SessionAuthentication',
          'rest_framework.authentication.BasicAuthentication',
      )
  }
  ```

3、路由中添加登录认证的配置

```
urlpatterns = [
    path('login/', TokenObtainPairView.as_view())
]

```



### 3、登录接口开发