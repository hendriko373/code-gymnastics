data Optional a =
    Nada
  | Only a
  deriving (Eq, Show)

instance Semigroup a => Semigroup (Optional a) where
    (<>) Nada o = o 
    (<>) o Nada = o
    (<>) (Only x) (Only y) = Only (x <> y)
    
instance Semigroup a => Monoid (Optional a) where
    mempty = Nada
