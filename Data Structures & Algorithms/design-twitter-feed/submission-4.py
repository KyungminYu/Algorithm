class Twitter:
    # To solve this problem, I will use heap for get latest feed, set for representing connection and list for each user's posts.

    # First, define posts, connections and time
    # Second, implement connecting follower and followee
    # Third, implement disconnectin follower and followee
    # Forth, implement postTweets by appending time and tweetId pair. time will be used for getting latest news feed.
    # Finally, implement getNewsFeed method. 
    # we have to make target userIds by merge user and its followers
    # Then traverse the each user's post and put them on the min heap.
    # if min heap size is larger than 10, then I will pop the oldest feed from min heap.
    # In ths way, we can maintain 10 latest news feeds. 

    def __init__(self):
        self.posts = defaultdict(list)
        self.connections = defaultdict(set)
        self.time = 0
        
    def postTweet(self, userId: int, tweetId: int) -> None:
        self.posts[userId].append([self.time, tweetId])
        self.time += 1

    def getNewsFeed(self, userId: int) -> List[int]:
        userIds = {userId} | self.connections[userId]
        latestPosts = []
        for uId in userIds:
            for post in self.posts[uId]:
                heapq.heappush(latestPosts, post)
                if len(latestPosts) > 10:
                    heapq.heappop(latestPosts)
        res = []
        while latestPosts:
            res.append(heapq.heappop(latestPosts)[1])
        return res[::-1]

    def follow(self, followerId: int, followeeId: int) -> None:
        if followerId == followeeId:
            return
        self.connections[followerId].add(followeeId)

    def unfollow(self, followerId: int, followeeId: int) -> None:
        if followerId == followeeId:
            return
        self.connections[followerId].discard(followeeId)
