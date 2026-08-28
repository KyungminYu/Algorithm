class Twitter:

    def __init__(self):
        self.posts = defaultdict(list)
        self.connection = defaultdict(set)
        self.time = 0
        

    def postTweet(self, userId: int, tweetId: int) -> None:
        self.time += 1
        self.posts[userId].append([self.time, tweetId])
        

    def getNewsFeed(self, userId: int) -> List[int]:
        userIds = {userId} | self.connection[userId]
        latestPosts = []

        for uId in userIds:
            for post in self.posts[uId]:
                heapq.heappush(latestPosts, [post[0], post[1]])
                if len(latestPosts) > 10:
                    heapq.heappop(latestPosts)

        res = []
        while latestPosts:
            res.append(heapq.heappop(latestPosts)[1])
        return res[::-1]
        

    def follow(self, followerId: int, followeeId: int) -> None:
        if followerId == followeeId:
            return
        self.connection[followerId].add(followeeId)
        

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followerId == followeeId:
            return
        self.connection[followerId].discard(followeeId)
