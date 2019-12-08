import Control.Monad
import Data.Char
import System.Exit

palindrome :: IO ()
palindrome = forever $ do
    line1 <- getLine
    case (flattened line1 == (reverse $ flattened line1)) of
        True  -> putStrLn "It's a palindrome!"
        False -> putStrLn "Nope"
    where 
        flattened = (map toLower) . filter isAlpha

type Name = String
type Age = Integer
data Person = Person Name Age deriving Show
data PersonInvalid = NameEmpty
    | AgeTooLow
    | PersonInvalidUnknown String
    deriving (Eq, Show)

mkPerson :: Name
         -> Age
         -> Either PersonInvalid Person
mkPerson name age
    | name /= "" && age > 0 = Right $ Person name age
    | name == ""            = Left NameEmpty
    | not (age > 0)         = Left AgeTooLow
    | otherwise             = Left $ PersonInvalidUnknown $
                              "Name was: " ++ show name ++
                              " Age was: " ++ show age

gimmePerson :: IO ()
gimmePerson = do
    putStrLn "Enter the name of a person:"
    name <- getLine
    putStrLn "Enter its age:"
    agestr <- getLine
    case (mkPerson name (read agestr)) of
        Right p -> putStrLn $ "Yay! " ++ show p
        Left l  -> putStrLn $ "Invalid input: " ++ show l
    return ()



