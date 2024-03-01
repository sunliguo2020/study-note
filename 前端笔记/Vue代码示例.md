# vue组件的基本代码示例

```vue
<script>
    export default {
      data() {
        return {
          count: 0
        }
      }
}
</script>

<template>
  <button @click="count++">You clicked me {{ count }} times.</button>
</template>
```

# uniapp中2种示例

```vue
<template>
	<view>
		
	</view>
</template>

<script >
	export default {
		onLoad(){
			console.log(this.getData())
		},
		methods:{
			getData(){
			  //获取分类列表id
			  uni.request({
			    url:"https://ku.qingnian8.com/dataApi/news/navlist.php",
			    success:res=>{
			     console.log(res)
			    }
			  })
			} 
		}
	}
</script>

<style lang="scss" scoped>

</style>

```

```vue

<template>
	<view></view>
</template>

<script setup>
	import {
		onLoad
	} from "@dcloudio/uni-app"
	onLoad((e) => {
		console.log(e);
		console.log(getData())
	})

	const getData = () => {
		//获取分类列表id
		uni.request({
			url: "https://ku.qingnian8.com/dataApi/news/navlist.php",
			success: res => {
				console.log(res)
			}
		})
	}
</script>

<style lang="scss" scoped>

</style>
```

# setup语法糖

在 Vue 3 中，`<script setup>` 是 Vue 单文件组件 (SFC) 的一种新语法糖，旨在简化组件的编写。这种语法糖特别适用于小型到中型组件，它允许你更简洁地编写组件逻辑，同时减少了不必要的样板代码。

在 `<script setup>` 中，你可以使用 `methods` 选项来定义组件的方法。不过，与传统的 `<script>` 语法相比，`<script setup>` 提供了一种更简洁的方式来定义方法。你可以直接在 `<script setup>` 内部定义函数，**而不必显式地使用 `methods` 选项**。

以下是一个简单的例子，展示了如何在 `<script setup>` 中定义和使用方法：

```vue
<template>  
  <button @click="incrementCount">Increment</button>  
  <p>Count: {{ count }}</p>  
</template>  
  
<script setup>  
import { ref } from 'vue'  
  
const count = ref(0)  
  
function incrementCount() {  
  count.value++  
}  
</script>
```

在这个例子中，我们定义了一个名为 `incrementCount` 的方法，该方法用于增加 `count` 的值。这个方法可以直接在 `<script setup>` 中定义，并且可以在模板中通过 `@click` 指令绑定到按钮的点击事件上。

需要注意的是，由于 `<script setup>` 的设计目标之一是简化代码，因此它**没有提供与 `this` 相关的上下文**。这意味着你不能在 `<script setup>` 中使用 `this` 来访问组件实例的属性或方法。相反，你应该使用 `ref`、`reactive` 等响应式 API 来管理组件的状态，并直接定义函数来处理逻辑。

总的来说，`<script setup>` 提供了一种更简洁、更直观的方式来编写 Vue 3 组件，特别是对于那些不需要复杂逻辑和状态的组件。然而，对于更复杂的组件，你可能仍然需要使用传统的 `<script>` 语法来提供更大的灵活性和控制力。

当然，以下是一个使用传统 `<script>` 语法的 Vue 3 组件示例：

```vue
<template>  
  <button @click="incrementCount">Increment</button>  
  <p>Count: {{ count }}</p>  
</template>  
  
<script>  
import { ref } from 'vue'  
  
export default {  
  name: 'Counter',  
  setup() {  
    const count = ref(0)  
  
    const incrementCount = () => {  
      count.value++  
    }  
  
    // 返回一个对象，包含组件的逻辑  
    return {  
      count,  
      incrementCount  
    }  
  }  
}  
</script>
```

在这个例子中，我们使用了 `setup` 函数来定义组件的逻辑。`setup` 函数是 Vue 3 引入的一个新的选项，用于替代 Vue 2 中的 `data`、`computed`、`methods` 等选项。在 `setup` 函数中，我们可以定义响应式数据、计算属性、方法等，并通过返回一个对象来暴露它们给模板。

在这个例子中，我们定义了一个 `count` 响应式引用，以及一个 `incrementCount` 方法。然后，我们通过返回一个包含 `count` 和 `incrementCount` 的对象，将它们暴露给模板。这样，模板就可以访问和使用这些数据和方法了。

需要注意的是，虽然这个例子使用了传统的 `<script>` 语法，但它仍然遵循了 Vue 3 的新特性和语法，如使用 `setup` 函数和 `ref` API 来管理组件的状态。

另外，`<script setup>` 语法实际上是 `<script>` 语法的一个简化版本，它允许你直接在组件的 `<script setup>` 标签内定义组件的逻辑，而不需要显式地导出一个对象。这使得代码更加简洁和直观，特别是在组件逻辑相对简单的情况下。

# `ref`、`reactive` 等响应式 API 来管理组件的状态

在 Vue 3 中，`ref` 和 `reactive` 是两个核心的响应式 API，它们用于创建和管理组件的状态。这些 API 是 Vue 3 的 Composition API 的一部分，它提供了一种更加灵活和可组合的方式来组织组件逻辑。

### ref

`ref` 函数用于创建一个响应式引用。它接受一个初始值，并返回一个响应式对象，该对象具有一个名为 `value` 的属性，用于访问和修改其值。当 `value` 被修改时，任何依赖于该引用的地方都会自动更新。

```javascript
import { ref } from 'vue'  
  
const count = ref(0) // 创建一个响应式引用，初始值为 0  
  
console.log(count.value) // 访问引用的值，输出 0  
  
count.value++ // 修改引用的值  
  
console.log(count.value) // 再次访问引用的值，输出 1
```

在模板中，你可以直接使用 `ref` 创建的响应式引用，而不需要通过 `.value` 访问器：

```vue
<template>  
  <p>Count: {{ count }}</p> <!-- 直接使用 count，不需要 count.value -->  
</template>  
  
<script>  
import { ref } from 'vue'  
  
export default {  
  setup() {  
    const count = ref(0)  
    return { count }  
  }  
}  
</script>
```

### reactive

`reactive` 函数用于创建一个响应式对象。与 `ref` 不同，`reactive` 创建的对象本身是响应式的，而不是它的属性。这意味着你可以直接修改对象的属性，而不需要像 `ref` 那样使用 `.value`。

```javascript
import { reactive } from 'vue'  
  
const state = reactive({  
  count: 0,  
  name: 'Alice'  
})  
  
console.log(state.count) // 访问响应式对象的属性，输出 0  
  
state.count++ // 直接修改响应式对象的属性  
  
console.log(state.count) // 再次访问响应式对象的属性，输出 1
```

在模板中，你也可以直接访问 `reactive` 创建的对象的属性：

```vue
<template>  
  <p>Count: {{ state.count }}</p>  
  <p>Name: {{ state.name }}</p>  
</template>  
  
<script>  
import { reactive } from 'vue'  
  
export default {  
  setup() {  
    const state = reactive({  
      count: 0,  
      name: 'Alice'  
    })  
    return { state }  
  }  
}  
</script>
```

### 使用场景

- 当你需要响应式地追踪单个值时，使用 `ref`。
- 当你需要响应式地追踪多个值并且希望以对象的形式组织它们时，使用 `reactive`。

### 注意事项

- `ref` 创建的响应式对象在模板中可以直接使用，不需要 `.value`，但在 JavaScript 代码中需要使用 `.value` 访问或修改其值。
- `reactive` 创建的对象本身就是响应式的，你可以直接修改它的属性，而不需要额外的操作。
- `ref` 和 `reactive` 创建的响应式对象都是 Vue 的响应式系统的一部分，当它们的值发生变化时，Vue 会自动更新依赖于这些值的部分。

通过使用 `ref` 和 `reactive`，你可以更加灵活和清晰地管理 Vue 组件的状态，并在需要时触发组件的重新渲染。