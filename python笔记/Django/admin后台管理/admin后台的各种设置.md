|                                   | 👉Django admin 模型选项(ModelAdmin) 【详细】查看              |                    |
| --------------------------------- | ------------------------------------------------------------ | ------------------ |
| 属性                              | 功能                                                         | 表达式             |
| actions                           | 给列表页面上提供额外操作功能                                 | 列表               |
| actions_on_top                    |                                                              |                    |
| actions_on_bottom                 | 控制操作栏在页面上的显示位置(默认actions_on_top = True; actions_on_bottom = False) | 布尔值             |
| actions_selection_counter         | 控制选择计数器是否显示在操作下拉列表旁边(默认actions_selection_counter = True) | 布尔值             |
| date_hierarchy                    | 设置为模型中的DateField或DateTimeField字段基于日期的分层筛选导航 | 字符串             |
| empty_value_display               | 此属性将覆盖记录字段为空（None，空字符串等）的默认显示值(默认值为-) | 字符串             |
| exclude                           | 表单中不展示的字段                                           | 元组               |
| fields                            | 在“添加”和“编辑”页面上的表单中进行简单的布局更改             | 元组               |
| fieldsets                         | 控制“添加”和“编辑”页面的布局, fieldsets是一个二元组列表，其中每个二元组代表管理表单页面上的<fieldset>, 这两个元组的格式为(name，field_options)，其中name是代表字段集标题的字符串，field_options是有关字段集的信息字典，包括要在其中显示的字段的列表。 |                    |
| field_options字典可以具有以下键： |                                                              |                    |
| 键                                | 值                                                           |                    |
| fields                            | 要在此字段集中显示的字段名称的元组。此键是必需的             |                    |
| classes                           | 包含要应用于该字段集的额外CSS类的列表或元组                  |                    |
| description                       | 一串可选的额外文本，将显示在每个字段集顶部，字段集标题下     |                    |
| 元组                              |                                                              |                    |
| filter_horizontal                 | 水平显示过滤器, 用于多对多模型(ManyToMany)                   | 元组               |
| filter_vertical                   | 垂直显示过滤器, 用于多对多模型(ManyToMany)                   | 元组               |
| form                              | 用于定制用户请求时候表单验证                                 | （类）模型         |
| formfield_overrides               | 提供了一种快捷方式来覆盖某些在管理员中使用的“Field”选项      | 字典               |
| inlines                           | 模型内联                                                     | 列表               |
| list_display                      | 控制列表页面上显示哪些字段                                   | 元组               |
| list_display_links                | 控制是否将list_display中的哪些字段链接到编辑页面             | 元组               |
| list_editable                     | 设置模型的字段允许在列表页面上进行编辑                       | 元组               |
| list_filter                       | 激活过滤器， 显示列表页面右侧栏中的过滤器                    | 元组               |
| list_max_show_all                 | 控制列表页面上的“显示全部”可以显示多少条数据(默认200)        | 数字               |
| list_per_page                     | 控制每个分页的列表页面上显示多少条数据(默认100)              | 数字               |
| list_select_related               | select_related()在列表页面上检索对象列表时使用               | 布尔值，列表或元组 |
| ordering                          | 设置默认排序字段                                             | 列表               |
| paginator                         | 用于分页的分页器类                                           | 类                 |
| prepopulated_fields               | 将字段名称映射到应预填充的字段                               | 字典               |
| preserve_filters                  | 在创建，编辑或删除对象后在列表视图上保留过滤器               | 布尔值             |
| radio_fields                      | 把外键或choice字段由下拉框变成单选框                         | 字典               |
| autocomplete_fields               | 自动补全， 针对外键设置                                      | 列表               |
| raw_id_fields                     | 自动补全外键或多对多字段内容，并且设置显示其id               | 元组               |
| readonly_fields                   | 设置为只读字段                                               | 元组               |
| save_as                           | 在表单上启用“另存为”功能(默认False)                          | 布尔值             |
| save_as_continue                  | 当save_as=True，节省了新对象后的默认重定向是该对象的编辑视图。如果设置了 save_as_continue=False，重定向将转到编辑列表视图。(默认True) | 布尔值             |
| save_on_top                       | 在表单顶部添加保存按钮(默认False)                            | 布尔值             |
| search_fields                     | 启用搜索框                                                   | 列表               |
| show_full_result_count            | 控制是否应在过滤的页面上显示对象的全部数量(默认True)         | 布尔值             |
| sortable_by                       | 允许的字段参与排序                                           | 列表，元组，集合   |
| view_on_site                      | 控制是否显示“查看站点”按钮是否显示(默认True)                 | 布尔值             |
|                                   |                                                              |                    |





## 设置表名为中文

在models.py中设置
```python
class Users(models.Model):
    _id = models.IntegerField()
    age = models.CharField('年龄', max_length=10)
    height = models.CharField('身高', max_length=10)
    ismeet = models.SmallIntegerField()

    class Meta:
        verbose_name = '会员信息'
        verbose_name_plural = verbose_name
```

## 设置App（应用）为中文
修改应用目录下的apps.py
