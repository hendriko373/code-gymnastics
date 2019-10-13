-- currying made explicit
s :: Integer -> Integer -> Integer
s a = h where 
    h :: Integer -> Integer
    h b = a + b

-- syntactic sugar
ss :: Integer -> Integer -> Integer
ss a b = a + b

t1 = ss 1 2 == s 1 2

sp = s 1
t2 = sp 2 == s 1 2

-- uncurrying
sunc :: (Integer, Integer) -> Integer
sunc (a, b) = a + b

t3 = sunc (1, 2) == s 1 2

sanon :: Integer -> Integer -> Integer
sanon = \a -> \b -> a + b

-- parametricity
f1 :: a -> a -> a
--f1 x y = x
f1 x = h where
    h y = x

f2 :: a -> a -> a
--f2 x y = y
f2 x = h where
    h :: a -> a
    h y = y

f3 :: a -> b -> b
f3 x y = y