`<script>` 和 `<script setup>` 是 Vue 3 中两种不同的脚本标签写法，主要用于 Vue 组件的定义。它们在使用方式、特性和目的上有所不同。

### `<script>`

这是 Vue 2 和 Vue 3 中都常见的写法，用于定义组件的逻辑。在 Vue 3 中，它通常与 `<template>` 和 `<style>` 标签一起使用，构成 SFC (Single File Component) 的三大部分。


```vue
<template>
  <!-- 组件的模板部分 -->
</template>

<script>
export default {
  data() {
    return {
      // 组件的数据
    };
  },
  methods: {
    // 组件的方法
  }
  // ... 其他选项，如 computed、watch、生命周期钩子等
}
</script>

<style scoped>
  /* 组件的样式部分 */
</style>
```
### `<script setup>`

`<script setup>` 是 Vue 3 引入的一种新的组件脚本编写方式，它是为了简化组件编写和减少样板代码而设计的。使用 `<script setup>` 时，你不需要显式地导出对象，因为编译器会为你处理这些。


```vue
<template>
  <!-- 组件的模板部分 -->
</template>

<script setup>
// 直接定义组件的数据和方法，不需要导出对象
const someData = ref(0);
const increment = () => {
  someData.value++;
};
</script>

<style scoped>
  /* 组件的样式部分 */
</style>
```
### 主要区别

1. **语法和结构**：`<script>` 需要显式地导出组件选项，而 `<script setup>` 则不需要，因为它利用了 ES6 的顶层语句和编译器魔法。
2. **可读性**：`<script>` 的写法更加明确和结构化，对于初学者来说可能更容易理解。而 `<script setup>` 的写法更加简洁，但可能需要一些时间来适应。
3. **用途**：`<script>` 是 Vue 2 和 Vue 3 的通用写法，而 `<script setup>` 是 Vue 3 特有的，用于简化组件编写。
4. **功能**：`<script setup>` 不支持某些 Vue 2 的特性，并且由于它的简洁性，某些高级特性（如 mixins、extends）在 `<script setup>` 中可能不那么容易使用。
5. **兼容性**：由于 `<script setup>` 是 Vue 3 的新特性，所以在 Vue 2 的项目中不能使用。

总的来说，`<script>` 和 `<script setup>` 都是有效的 Vue 组件脚本编写方式，选择哪种方式取决于你的项目需求、团队习惯和个人喜好。

# 问题一  data ，methods 和setup可以一起写吗？