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

这里说是二分查找，其实严格来说是三分，mid 值有三种情况，分别是大于、小于、等于，对应这三种情况分别更新 left、right，或者返回最终结果。

很多时候，可以实现严格的二分，使得 left 包括小于等于的情况，right包含大于的情况，这时候循环的终止条件也要适当更改，保证不会死循环并且得到最终结果，具体可以看下面的旋转数组的例子。

# 二分查找的变体

**对于排序的数组进行查找，二分查找总是应该首先考虑的解决办法。**

## 1 统计数字在排序数组中出现的次数

简单思路，先用二分查找算法找到一个 target，由于 target 可能出现多次，于是在找到的位置向左右顺序扫描，分别找出第一个和最后一个 target。最差情况下，扫描的时间复杂度能达到O(n)。因此这种方法和从头到尾扫描整个数组统计出现的次数的方法是一样的，效率不够高。

因此可以考虑用二分查找直接找出重复出现的数字的第一个位置和最后一个位置。找出数字第一次出现位置的实现如下，保证了最坏情况下时间复杂度仍然为 O(logn)：

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
                    right = mid-1;  // 不断向左逼近
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

## 2 旋转数组的最小数字

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。输入一个**非递减序列**的一个旋转，输出旋转数组的最小元素。例如数组{3,4,5,1,2}为{1,2,3,4,5}的一个旋转，该数组的最小值为1。

如果数组中没有重复数字，情况比较简单。可以通过比较 mid 和 left（或者right）的值，如果

1. nums[mid] >= nums[left]: 说明 mid 在旋转数组的左半部分（之所以有=这种情况，是因为 mid 可能等于 left）；
2. nums[mid] < nums[left]: 说明 mid 在旋转数组的右半部分。

判断出 mid 的位置后，需要恰当地去更新 left，right 的值，更新策略的选择将会直接决定 while 循环结束条件。这里我们让 left 位于旋转数组的左半部分，right位于右半部分，循环条件为 left < right。对于left 的更新每次多向右多移动一个位置：mid+1，right 每次更新为 mid，这样当循环终止时，left和right值相同，并且left指向了最小的数字。

    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;

        while(left<right){
            // When there is no rotate, just return self.nums[start]
            if(nums[left]<nums[right])  return nums[left];
            int mid = left + (right-left) / 2;
            if(nums[left] <= nums[mid]){
                left = mid+1;
            }
            else{
                right = mid;
            }
        }
        return nums[left];
    }

如果数组中有重复的数字，那么情况稍微有点复杂，当nums[mid] == nums[left] 时，我们没法判断 mid 在哪一边，因此选择对 left 进行简单的 +1 操作。

    int findMin(vector<int>& nums) {
        int left=0;
        int right=nums.size()-1;
        while(left<right){
            if(nums[left] < nums[right])   return nums[left];
            int mid = left + (right-left)/2;
            if(nums[left] < nums[mid]){
                left = mid+1;
            }
            else if(nums[left] > nums[mid]){
                right = mid;
            }
            else{
                left += 1;
            }
        }
        return nums[left];
    }



# 参考  
[Binary search algorithm](https://en.wikipedia.org/wiki/Binary_search_algorithm)  
[数据库中二分查找相关问题](http://hedengcheng.com/?p=595)  


[1]: http://7xrlu9.com1.z0.glb.clouddn.com/Algorithm_BinarySearch_1.png

