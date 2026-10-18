class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        # To address this problem, I will use max heap, 
        # However, python's build in heap data structure is min heap.
        # In this regard, I will use negative values to make it max heap
        # First, collect the each value's frequency in the nums array to the count dictionary
        # Then, put negative_value-key pairs to the pq array and heapify it later.
        # Finally, pop the negative_value-key pairs and put key to the res array k times. In this way, I can find k the most frequent elements.
        count = {}
        for n in nums:
            if n not in count:
                count[n] = 0
            count[n] += 1
        pq = []
        for key in count.keys():
            pq.append([-count[key], key])
        heapq.heapify(pq)

        res = []
        for _ in range(k):
            res.append(heapq.heappop(pq)[1])
        return res