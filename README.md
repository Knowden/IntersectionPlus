# IntersectionPlus

> 千万不要用于任何严肃场合的交点计算器

## core.dll使用说明

要使用core.dll，您需要：

1. 将当前项目的所有.h拷贝于您的工程目录下
2. 将core.lib和core.dll拷贝到您的工程目录下，并修改链接器配置

### core.dll接口说明

core.dll中包装了一个core类，使用该类的方法可以支持基本所需功能

```c++
class _declspec(dllexport) core {
private:
	Solution s;

public:
	void add_component(std::string component);
    void delete_line_component(int id);
	void delete_circle_component(int id);
    
	std::unordered_set<Point> get_all_intersection(bool force);
	std::vector<Line> get_all_line();
	std::vector<Circle> get_all_circle();
};
```

#### add_component(std::string)

接收任意字符串，core会进行错误的处理，但若想正常使用，请按规范输入

注意：该函数可能抛出输入非法异常，请注意捕获

#### get_all_intersection(bool)

可获取所有交点集合

可传入一个bool值，当该值为true时，会强制core重新计算交点集合，否则将保持原有状态（初始状态为空）

注意：该函数可能抛出异常，当存在component之间有无穷交点时

#### get_all_line()

获取当前输入过的所有线

#### get_all_circle()

获取当前输入过的所有圆

#### delete_line_component(int id)

根据id删除对应的线

#### delete_circle_component(int id)

根据id删除对应的圆