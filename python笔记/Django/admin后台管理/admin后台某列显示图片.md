

format_html和mark_safe非常类似，本质还是调用mark_safe函数，不同在于传参方式，mark_safe直接传递完整的html字符串；

而format_html需要使用{}占位符：

```python
@admin.register(models.XingFuAnLi)
class XingFuAnLiAdmin(admin.ModelAdmin):
    list_display = ['id', '_id', 'title', 'content', 'avatar_tag', 'imgurl']

    def avatar_tag(self, obj):
        """
        显示头像列
        :param obj:
        :return:
        """
        if obj.avatar:
            return format_html(f'<img src="{obj.avatar.url}" width="50" height="50"/>')
        return ""
```

