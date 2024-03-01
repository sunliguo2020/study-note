异步调用，回调地狱

```javascript
getData(){
  //获取分类列表id
  uni.request({
    url:"https://ku.qingnian8.com/dataApi/news/navlist.php",
    success:res=>{
      let id=res.data[0].id
      // 根据分类id获取该分类下的所有文章
      uni.request({
        url:"https://ku.qingnian8.com/dataApi/news/newslist.php",
        data:{
          cid:id
        },
        success:res2=>{
          //获取到一篇文章的id，根据文章id找到该文章下的评论
          let id=res2.data[0].id;
          uni.request({
            url:"https://ku.qingnian8.com/dataApi/news/comment.php",
            data:{
              aid:id
            },
            success:res3=>{
              //找到该文章下所有的评论
              console.log(res3)
            }
          })
        }
      })

    }
  })
} 
```



```vue

<template>
	<view>
	</view>
</template>

<script>
	export default {
		data() {
			return {
				title:'hello world'
			}
		},
		methods: {
			
		},
		onLoad(){
			let p = new Promise((resolve,reject)=>{
				uni.request({
					url:'http://ku.qingnian8.com/dataApi/news/navlist.php2',
					success:res=>{
						// console.log(res);
						// resolve(res);
					},
					fail:err=>{
						reject(err)
					}
				})
			});
			console.log(p);
			p.then(res=>{
				console.log(res);
			}).catch(err=>{
				console.log(err)
			});
		}
	}
</script>

<style>

</style>

```

