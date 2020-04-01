module ReaderPractice where

x = [1, 2, 3]
y = [4, 5, 6]
z = [7, 8, 9]

xs :: Maybe Integer
xs = lookup 3 $ zip x y

ys :: Maybe Integer
ys = lookup 6 $ zip y z

zs :: Maybe Integer
zs = lookup 4 $ zip x y

z' :: Integer -> Maybe Integer
z' n = lookup n $ zip x z

x1 :: Maybe (Integer, Integer)
x1 = (,) <$> xs <*> ys

x2 :: Maybe (Integer, Integer)
x2 = (,) <$> ys <*> zs

x3 :: Integer -> (Maybe Integer, Maybe Integer)
x3 = (,) <$> z' <*> z'

summed :: Num c => (c, c) -> c
summed = uncurry (+)

bolt :: Integer -> Bool
bolt = (&&) <$> (>3) <*> (<8)
-- f <$> g <*> h = \r -> (f.g) r (h r)

fromMaybe :: a -> Maybe a -> a
fromMaybe d Nothing  = d
fromMaybe _ (Just a) = a

main :: IO ()
main = do
    print $ sequenceA [Just 3, Just 2, Just 1]
    print $ sequenceA [x, y]
    print $ sequenceA [xs, ys]
    print $ summed <$> ((,) <$> xs <*> ys)
    print $ fmap summed ((,) <$> xs <*> zs)
    print $ bolt 7
    print $ fmap bolt z
    print $ sequenceA [(>3), (<8), even] 7
    print $ foldr (&&) True $ sequA 6
    print $ sequA $ fromMaybe 0 s'
    print $ sequA $ fromMaybe 0 ys

-- sequenceA []     = []
-- sequenceA (f:fs) = (:) <$> f <*> sequenceA fs
-- hence if f :: r -> a
-- sequenceA (f:fs) = (:) . f <*> sequenceA fs

sequA :: Integral a => a -> [Bool]
sequA = sequenceA [(>3), (<8), even]

s' :: Maybe Integer
s' = summed <$> ((,) <$> xs <*> ys)
