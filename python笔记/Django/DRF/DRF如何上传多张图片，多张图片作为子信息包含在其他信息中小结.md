## 【drf】如何上传多张图片，多张图片作为子信息包含在其他信息中小结


every blog every motto: There’s only one corner of the universe you can be sure of improving, and that’s your own self.
https://blog.csdn.net/weixin_39190382?spm=1010.2135.3001.5343

0. ## 前言

   如何使用drf 上传多张图片？图片信息是其他信息的中的其中一个子信息，该如何上传呢？

说明：
代码进行了脱敏处理，可能存在一定不完整现象，但总体逻辑是通的！

1. ## 正文

  ## 1.1 需求

  我们需要在上传的信息中包含包含（多张）图片信息，比如：

学生课程信息，里面包含课程的课程的书籍的图片，那么改如何做呢？

刚开始想的是一个字段包含多个信息，即一个图片字段包含多张图片，擦，，，走了弯路，，，，

后来又想着怎么在课程信息里面嵌套（外键）图片信息，，，，，，，

说多都是泪，，，，，害，

言归正传，虽然我们的逻辑上式课程信息中包含图片信息，但在代码上并不是放在里面，如下代码：



```python
class couInfo(models.Model):
    # img = models.ImageField(max_length=100, verbose_name='图片',
    # img = models.ForeignKey(imgInfo, on_delete=models.CASCADE)
    name = models.CharField(verbose_name=_('课程名称'), max_length=90)
```

上面的代码是不对的，

## 1.2 代码实现

1. model
课程数据表

```python
class couInfo(models.Model):
	name = models.CharField(verbose_name=_('课程名称'), max_length=90)
```

图片信息表

```python
class ImgInfo(models.Model):
    img = models.ImageField(max_length=100, upload_to='avatar_img/', default='img.png', verbose_name='图片',
                            null=True, blank=True)
    couinfo= models.ForeignKey(couInfo,on_delete=models.CASCADE,related_name='img')
```
注意：
这里是重点！！！！！

图片不是写在课程信息里面  相反，课程作为图片信息的外键，放入图片信息里面
在图片信息的数据表中，有一列会保存课程信息表的id，这样二者就能对应上了
数据进行了脱敏处理，自行补上class Meta信息

2. 序列化
    图片信息表序列化

  ```python
  class imgInfoSerializer(serializers.ModelSerializer):
      class Meta:
          model = ImgInfo
          fields = '__all__'
  ```


  课程信息表序列化

```python

class courSerializer(serializers.ModelSerializer):
    img = serializers.HyperlinkedRelatedField(
        many=True,
        read_only=True,
        view_name='tg'
    )

    class Meta:
        model = couInfo
        # fields = '__all__'
        fields = ['name', 'img']
    
    def create(self, validated_data):
        s_obj = couInfo.objects.create(**validated_data)
        img_data = self.context['request'].FILES.getlist('img')

        for ele in img_data:
            ImgInfo.objects.create(couinfo=s_obj , img=ele)

        return s_obj 
```


注意： 这里的view_name的值！！！！

3. 视图
   图片信息视图

   
   
   ```python
     class ImgInfoDetailView(APIView):
        def get_object(self, pk):
            try:
                return ImgInfo.objects.get(pk=pk)
            except ImgInfo.DoesNotExist:
                raise Http404
        def get(self, request, pk, format=None):
            context = {"request": request}
            article = self.get_object(pk)
            serializer = imgInfoSerializer(article, context=context)
            return Response(serializer.data)
   ```


课程信息视图大同小异，这里不赘述

4. url
app中的url



```python
          urlpatterns = [
                  re_path(r'^sellimg/(?P<pk>[0-9]+)$', views_api.ImgInfoDetailView.as_view(),name='tg'),
          ] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
```

注意：
这里的name的值，就是我们在HyperlinkedRelatedField中需要填写的view_name的值！！！！！
这里的name的值，就是我们在HyperlinkedRelatedField中需要填写的view_name的值！！！！！
这里的name的值，就是我们在HyperlinkedRelatedField中需要填写的view_name的值！！！！！

参考
全网！！！！