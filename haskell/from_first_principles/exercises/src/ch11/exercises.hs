import Data.Char
import Data.List

data Price = Price Integer 
    deriving (Eq, Show)

data Size = Size Integer
    deriving (Eq, Show)

data Manufacturer = 
    Mini 
    | Mazda 
    | Tata 
    deriving (Eq, Show)

data Airline = 
    PapuAir 
    | CatapultsR'Us 
    | TakeYourChancesUnited 
    deriving (Eq, Show)

data Vehicle =
    Car Manufacturer Price
    | Plane Airline Size
    deriving (Eq, Show)

myCar = Car Mini (Price 14000)
urCar = Car Mazda (Price 20000)
clownCar = Car Tata (Price 7000)
doge = Plane PapuAir (Size 200)

isCar :: Vehicle -> Bool
isCar (Car _ _)  = True
isCar _  = False

isPlane :: Vehicle -> Bool
isPlane (Plane _ _) = True
isPlane _ = False

areCars :: [Vehicle] -> Bool
areCars = all isCar

getManu :: Vehicle -> Manufacturer
getManu (Car m _) = m

data BinaryTree a =
    Leaf
  | Node (BinaryTree a) a (BinaryTree a)
  deriving (Eq, Ord, Show)

mapTree :: (a -> b) -> BinaryTree a -> BinaryTree b
mapTree _ Leaf = Leaf
mapTree f (Node left a right) = 
    Node (mapTree f left) (f a) (mapTree f right)

preorder :: BinaryTree a -> [a]
preorder Leaf = []
preorder (Node left a right) = a : (preorder left ++ preorder right)

inorder :: BinaryTree a -> [a]
inorder Leaf = []
inorder (Node left a right) = inorder left ++ [a] ++ inorder right

postorder :: BinaryTree a -> [a]
postorder Leaf = []
postorder (Node left a right) = (postorder left ++ postorder right) ++ [a]

instance Foldable BinaryTree where
    foldr f z tree = foldr f z $ inorder tree

-- Language exercises

isSubseqOf :: (Eq a) => [a] -> [a] -> Bool
isSubseqOf [] _ = True
isSubseqOf _ [] = False
isSubseqOf xs@(x:xt) (y:yt)
    | (x == y) = isSubseqOf xt yt
    | otherwise = isSubseqOf xs yt

capitalizeWords :: String -> [(String, String)]
capitalizeWords s = map capitalize $ words s
    where
        capitalize xs@(x:xt) = (xs, toUpper x : xt)

capitalizeWord :: String -> String
capitalizeWord "" = ""
capitalizeWord (' ':xs) = ' ' : capitalizeWord xs
capitalizeWord (x:xs) = toUpper x : xs

capitalizeParagraph :: String -> String
capitalizeParagraph s = concat $ map capitalizeWord (splitOn '.' s)

splitOn :: Char -> String -> [String]
splitOn c = foldr f [[]] 
            where 
                f c' xs@(x:xt) 
                    | c' == c = [c'] : xs 
                    | otherwise = (c':x):xt


sentences :: String -> [String]
sentences s = case dropWhile (\c -> c == '.' || isSpace c) s of
                "" -> []
                s' -> sentence : sentences s''
                    where (sentence, s'') = break (== '.') s'

unsentences :: [String] -> String
unsentences (x:[]) = x ++ "."
unsentences (x:xs) = x ++ ". " ++ unsentences xs

-- Phone exercise
type Digit = Char
type Presses = Int
data Key = Key
    { digit :: Digit
    , chars :: [Char]
    } deriving Show
data Phone = Phone [Key]

myPhone = Phone
    [ Key '1' ['1']
    , Key '2' ['a', 'b', 'c', '2']
    , Key '3' ['d', 'e', 'f', '3']
    , Key '4' ['g', 'h', 'i', '4']
    , Key '5' ['j', 'k', 'l', '5']
    , Key '6' ['m', 'n', 'o', '6']
    , Key '7' ['p', 'q', 'r', 's', '7']
    , Key '8' ['t', 'u', 'v', '8']
    , Key '9' ['w', 'x', 'y', 'z', '9']
    , Key '*' []
    , Key '0' [' ', '0']
    , Key '#' ['.', ',']
    ]

convo =
    [ "Wanna play 20 questions"
    , "Ya"
    , "U 1st haha"
    , "Lol ok. Have u ever tasted alcohol lol"
    , "Lol ya"
    , "Wow ur cool haha. Ur turn"
    , "Ok. Do u think I am pretty Lol"
    , "Lol ya"
    , "Haha thanks just making sure rofl ur turn"
    ]

presses :: Phone -> Char -> Maybe (Digit, Presses)
presses (Phone keys) c =
    case find (elem c . chars) keys of
        Nothing -> Nothing
        Just k ->
            case elemIndex c (chars k) of
                Nothing -> Nothing
                Just p -> Just (digit k, p + 1)

reverseTaps :: Phone -> Char -> [(Digit, Presses)]
reverseTaps p c =
    case presses p $ toLower c of
        Nothing -> error "Character not represented on phone"
        Just (d, p) -> 
            if isUpper c then [('*', 1), (d, p)] else [(d, p)]

cellPhonesDead :: Phone -> String -> [(Digit, Presses)]
cellPhonesDead p =
    foldr ((++) . reverseTaps p) [] 

fingerTaps :: [(Digit, Presses)] -> Presses
fingerTaps = foldr ((+) . snd) 0

-- Hutton's razor

data Expr 
    = Lit Integer
    | Add Expr Expr

eval :: Expr -> Integer
eval (Lit n) = n
eval (Add e1 e2) = eval e1 + eval e2

printExpr :: Expr -> String
printExpr (Lit n) = show n
printExpr (Add e1 e2) = printExpr e1 ++ " + " ++ printExpr e2