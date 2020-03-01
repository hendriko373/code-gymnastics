data List a =
    End
  | Cons a (List a)

instance Foldable List where
    foldmap :: Monoid m => (a -> m) -> List a -> m
    foldmap _ End         = mempty
    foldmap f (Cons a as) = (f a) <> foldmap f as 
