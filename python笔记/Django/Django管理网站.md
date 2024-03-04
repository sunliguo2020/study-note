# 自动后台管理应用

### 1、settings.py中设置 admin

```python
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'app01.apps.App01Config',
]
```

### 创建超级用户

```python
python manage.py createsuperuser
```

数据库中添加 auth_user 添加一条记录

#### 向管理网站注册模型app01目录下的admin.py

```python
from django.contrib import admin
from . import models
from .models import HisInformation

# Register your models here.
admin.site.register(models.Shoujihao)


@admin.register(HisInformation)
class HisInformationAdmin(admin.ModelAdmin):
    list_display = ('id', 'idcard', 'year') 

```

#### url.py

```python
urlpatterns = [
    path('admin/', admin.site.urls),
]

```

