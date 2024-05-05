```python
class WorkersListView(View):
    """
        显示workers原始数据的视图类
        先过滤 后分页
        request ==>FilterClass ==>Paginator ==>paginator.get_page(page) ==>context['page_obj']
    """

    def get(self, request):
        # 过滤
        f = WorkersFilter(request.GET, queryset=models.Workers.objects.filter(is_delete=0))
        # 实例化一个分页对象，每页显示
        paginator = Paginator(f.qs, 20)
        # 从URL通过get页码，如?page=2
        page = request.GET.get('page', '1')
        # 获取某页的对象
        page_obj = paginator.get_page(page)

        context = {
            # filter 过滤后的分页数据
            'page_obj': page_obj,
            'paginator': paginator,
            'is_paginated': True,
            'filter': f,
            'max_left_item_count': 10
        }
        return render(request, 'shbz/workers_list.html', context)

```

