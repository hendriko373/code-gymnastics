import Data.Bits
import Control.Monad
import Control.Applicative

-- Return (x, y, d) where
-- d = gcd(a, b) = x*a + y*b
extGcd :: Int -> Int -> (Int, Int, Int)
extGcd a b 
    | a < 0  = let (x, y, d) = extGcd (-a) b in (-x, y, d)
    | b < 0  = let (x, y, d) = extGcd a (-b) in (x, -y, d)
    | b == 0 = (1, 0, a)
    | otherwise =
        let (q, r) = quotRem a b
            (s, t, d) = extGcd b r
         in (t, s - q*t, d)

-- The multiplicative inverse of a in F_p
inv :: Int -> Int -> Maybe Int
inv a p = 
    let (a', k, d) = extGcd a p
        a'' = if a' < 0 then a' + p else a'
     in if d == 1 then Just a'' else Nothing

data Point = 
    Unit 
  | Point
      { x :: Int
      , y :: Int }
    deriving (Eq, Show)

-- Return the sum of two points on the curve
-- y^2 = x^3 + 7 according to the group structure
-- on elliptic curves over finite fields F_p.
add :: Int -> Point -> Point -> Maybe Point
add _ Unit h    = Just h 
add _ g    Unit = Just g 
add p g    h     
  | (x g) == (x h) && (y g) `mod` p == (-(y h)) `mod` p = Just Unit
  | otherwise =
      let 
        m = flip mod p <$>
            if g == h
               then (*(3*(x g)^2)) <$> inv (2*(y g)) p
               else (*((y g) - (y h))) <$> inv ((x g) - (x h)) p
        go Nothing = Nothing
        go (Just n) = Just Point
               { x = (n^2 - (x g) - (x h)) `mod` p
               , y = ((-n)*(n^2 - 2*(x g) - (x h)) - (y g)) `mod` p
               }
       in go m

-- The order n of a generating point g, i.e, n * g = e, 
-- or g = (n + 1) * g.
order :: Int -> Point -> Int
order p g =
    let go Nothing n  = n
        go (Just h) n = 
            if h == g
               then n
               else go (add p h g) (n + 1)
          in go (add p g g) 1

bits :: Int -> [Bool]
bits w = map (\x -> testBit w x) [0..(finiteBitSize w)]

-- Scalar multiplication making of the binary rep of the multiplier
mult :: Int -> Int -> Point -> Maybe Point
mult p n g =
    foldr ((join .) . (liftA2 (add p))) (Just Unit) $
        zipWith (\b gg -> if b then gg else Just Unit) 
            (bits n) 
            (iterate (join (add p) =<<) (Just g))

-- Brute force scalar multiplication
multBrute :: Int -> Int -> Point -> Maybe Point
multBrute p n g = 
    foldr go (Just Unit) $ take n $ repeat g 
        where go = (join .) . fmap . (add p)


-- Refactor with newtype that encodes a finite field
--
-- The p should be shared across the type values
--  ~ newtype WordF p = WordF Integer/Word 
data WordF = WordF
    { p :: Word
    , a :: Word
    }
    deriving (Eq, Show)

unwrap :: WordF -> WordF
unwrap (WordF p a) = WordF p (a `mod` p)

