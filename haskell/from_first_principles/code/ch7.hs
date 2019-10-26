functionC :: Ord a => a -> a -> a
functionC x y =
    case x > y of
        True -> x
        False -> y

ifEvenAdd2 :: Integral a => a -> a
ifEvenAdd2 x =
    case even x of
        True -> x + 2
        False -> x

dodgy x y = x + y * 10
oneIsOne = dodgy 1
oneIsTwo = (flip dodgy) 2

numbers x
    | x < 0     = -1
    | x == 0    = 0
    | x > 0     = 1

foldBool3 :: a -> a -> Bool -> a
foldBool3 x y b =
    case b of
        True -> x
        False -> y
        
foldBool4 :: a -> a -> Bool -> a
foldBool4 x y b
        | b == True = x
        | otherwise = y

g :: (a -> b) -> (a, c) -> (b, c)
g f (x, y) = (f x, y)

roundTrip :: (Show a, Read a) => a -> a
roundTrip x = read . show $ x