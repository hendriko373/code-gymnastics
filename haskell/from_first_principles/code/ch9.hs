myHead :: [a] -> Maybe a
myHead [] = Nothing
myHead (x : xs) = Just x

eftBool :: Bool -> Bool -> [Bool]
eftBool False False = [False]
eftBool True True = [True]
eftBool False True = [False, True]
eftBool True False = []

eftInt :: Int -> Int -> [Int]
eftInt x y 
    | x > y = []
    | otherwise = x : eftInt (x + 1) y

efInt :: Int -> [Int]
efInt x = x : efInt (x + 1)

myWords :: String -> [String]
myWords = breakString ' '

firstSen = "Tyger Tyger, burning bright\n"
secondSen = "In the forests of the night\n"
thirdSen = "What immortal hand or eye\n"
fourthSen = "Could frame thy fearful symmetry?"
sentences = firstSen ++ secondSen
                ++ thirdSen ++ fourthSen

myLines :: String -> [String]
myLines = breakString '\n'

breakString :: Char -> String -> [String]
breakString c [] = []
breakString c s = (takeWhile (/= c) s) 
                    : (breakString c $ drop 1 $ dropWhile (/= c) s)
