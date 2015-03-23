import qualified Data.Map as Map
import qualified Data.Set as Set

newtype State s t = State (s -> (t, s))

instance Monad (State s) where
    return x = State $ \s -> (x,s)
    (State h) >>= f = State $ \s -> let (a, newState) = h s
                                        (State g) = f a
                                    in  g newState

get :: State t t
get = State $ \s -> (s, s) -- Examine the state at this point in the computation.
put :: s -> State s ()
put s = State $ \_ -> ((), s) -- Replace the state.
modify :: (s -> s) -> State s ()
modify f = State $ \s -> ((), f s) -- Update the state
runState :: State s a -> s -> (a, s)
runState (State t) s = t s

execState :: State b a -> b -> b
execState t s = snd $ t `runState` s
evalState :: State b a -> b -> a
evalState t s = fst $ t `runState` s

gets :: (t -> b) -> State t b
gets f = do
  v <- get
  return $ f v

type Key = Int
type Label = Int
type Node = (Label, Key)
type Graph = Map.Map Key [Node]
type ProtoNode = (Key, Node)

readData :: IO Graph
readData = do
  str <- getContents
  let parsed = parseData $ drop 1 $ lines str
  return parsed

mAdd :: Node -> Maybe [Node] -> Maybe [Node]
mAdd node Nothing = Just [node]
mAdd node (Just nodes) = Just (node:nodes)

createNode :: ProtoNode -> State Graph ()
createNode (from_node, node) = modify (Map.alter (mAdd node) from_node )

parseData :: [String] -> Graph
parseData ls = mapM_ (createNode . to3Int) ls `execState` Map.empty

to3Int :: String -> ProtoNode
to3Int l = let [a,b,c] = map (read :: String -> Int) $ words l in (a,(b,c))

type Path = [Node]
type Step = (Key, Path)
type Visited = Set.Set Label
data DFS = DFS { to :: Key, graph :: Graph, visited :: Visited } deriving Show
find0Cycle :: Graph -> Path
find0Cycle gr = findPath DFS { to = 0, graph = gr, visited = Set.empty} [(0, [])]

findPath :: DFS -> [Step] -> Path
findPath dfs steps = lookForPath steps `evalState` dfs

lookForPath :: [Step] -> State DFS Path
lookForPath [] = return []
lookForPath (cur:next)= do
  nexts <- dfsStep cur
  finalPath <- checkIfDone nexts
  case finalPath of
    ((_, path):_) -> return path
    [] -> lookForPath (nexts ++ next)

checkIfDone :: [Step] -> State DFS [Step]
checkIfDone nexts = do
  dfs <- get
  return $ filter (\(key,_) -> key == to dfs) nexts

dfsStep :: Step -> State DFS [Step]
dfsStep (key, path) = do
  visitd <- getVisited
  if key `Set.member` visitd
  then return []
  else do
    markAsVisited key
    neighbourNodes <- findNeighbourNodes key
    return $ makeVisitOptions neighbourNodes path

getVisited :: State DFS Visited
getVisited = gets visited

markAsVisited :: Key -> State DFS ()
markAsVisited key = do
  dfs <- get
  put dfs { visited = key `Set.insert` visited dfs }

findNeighbourNodes :: Key -> State DFS [Node]
findNeighbourNodes key = do
  dfs <- get
  let mNodes = key `Map.lookup` graph dfs
  return $ maybeToList mNodes

maybeToList :: Maybe [Node] -> [Node]
maybeToList Nothing = []
maybeToList (Just xs) = xs

makeVisitOptions :: [Node] -> Path -> [Step]
makeVisitOptions toVisit path = map (\x@(_, key) -> (key, x:path)) toVisit

makeEdgeList :: Key -> Path -> [(Key, Label, Key)]
makeEdgeList _ [] = []
makeEdgeList v ((label, next):xs) = (v, label, next): makeEdgeList next xs

main :: IO ()
main = do
  dat <- readData
  let solutions = find0Cycle dat
  if null solutions
  then putStrLn "BRAK"
  else do
    print $ length solutions
    let edgeList = makeEdgeList 0 $ reverse solutions
    mapM_ (\(a,b,c) ->putStrLn $ show a ++ " " ++ show b ++ " " ++ show c
      ) edgeList
