我看了 dj 算法的堆优化，发现应该是需要一个修改节点值的操作的，但是我转念一想，STL 中的 priority_queue 没有这个操作都可以实现堆优化，那为什么我的堆就要支持呢？遂没有 decreasing_key 操作。望周知

-- Vanadium