`二分查找算法`（binary search）是一种在有序数组中查找某一特定元素的算法。搜索过程从数组的中间元素开始，如果中间元素正好是要查找的元素，则搜索过程结束；如果某一特定元素大于或者小于中间元素，则在数组大于或小于中间元素的那一半中查找，而且跟开始一样从中间元素开始比较。如果在某一步骤数组为空，则代表找不到。这种搜索算法每一次比较都使搜索范围缩小一半，因此时间复杂度为 logn。

![][1]

算法看起来十分简单，但要注意相关的几个问题：

* 递归还是迭代？
* 递归实现时，检查参数的有效性（low/high参数）；
* 计算二分查找中的中值时防止溢出；
* 如何查找第一个/最后一个等值？
 
# 简单实现

下面来看下简单二分查找（数组中不包含重复数字）的两种实现方案。

递归实现如下：

    // 在 nums[begin, end) 中查找 target
    int binary_search(const vector<int> &nums, int begin, int end, int target){
        if(begin<0 || begin>=end || end>nums.size()){
            return -1;
        }
        int mid = begin + (end-1 - begin)/2;
        if(nums[mid] > target){
            return binary_search(nums, begin, mid, target);
        }
        else if(nums[mid] < target){
            return binary_search(nums, mid+1, end, target);
        }
        else{
            return mid;
        }
    }

循环实现如下：

    int binary_search(const vector<int> &nums, int target){
        int left = 0;
        int right = nums.size() - 1;
        while(left <= right){
            int mid = left + (right-left) / 2; // 防止溢出
            // int mid = (left+right)/2  
            if(nums[mid] > target){
                right = mid - 1;
            }
            else if(nums[mid] < target){
                left = mid + 1;
            }
            else{
                return mid;
            }
        }
        return -1; // 没有找到target
    }


# 二分查找的变体

### 统计一个数字在排序数组中出现的次数。

简单思路，先用二分查找算法找到一个 target，由于 target 可能出现多次，于是在找到的位置向左右顺序扫描，分别找出第一个和最后一个 target。最差情况下，扫描的时间复杂度能达到O(n)。因此这种方法和从头到尾扫描整个数组统计3出现的次数的方法是一样的，效率不够高。

因此可以考虑用二分查找直接找出重复出现的数字的第一个位置和最后一个位置。找出数字第一次出现位置的实现如下：

    // 在 nums[begin, end) 中查找 target
    int getFirstK(int nums[], int length, int k){
        int left = 0;
        int right = length-1;
        while(left<=right){
            int mid = left + (right-left)/2;
            if(nums[mid] < k){
                left = mid + 1;
            }
            else if(nums[mid] > k){
                right = mid - 1;
            }
            else{
                if(mid > 0 && nums[mid-1] == k){
                    right = mid-1;
                }
                else{
                    return mid;
                }
            }
        }
        return -1;
    }

找到最后一次出现位置的代码，只需要在 mid == k 时稍作处理即可。

    if(mid+1 < length && nums[mid+1] == k){
        left = mid+1;
    }


# 参考  
[Binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)  
[数据库中二分查找相关问题](http://hedengcheng.com/?p=595)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_BinarySearch_1.png

