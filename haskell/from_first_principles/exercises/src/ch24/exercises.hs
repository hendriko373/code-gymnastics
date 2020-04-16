import Text.Trifecta
import Control.Applicative
import Data.Char

--1. semantic versioning
data NumberOrString =
    NOSS String
  | NOSI Integer
    deriving Show

type Major = Integer
type Minor = Integer
type Patch = Integer
type Release = [NumberOrString]
type Metadata = [NumberOrString]

data SemVer =
    SemVer Major Minor Patch Release Metadata
    deriving Show

parseSemVerM :: Parser SemVer
parseSemVerM = do
    major <- integer
    char '.'
    minor <- integer
    char '.'
    patch <- integer
    let pp = (NOSS <$> some letter <|> NOSI <$> integer)
    release <- option [] $ try $ char '-' >> sepBy pp (char '.')
    metadata <- option [] $ char '+' >> sepBy pp (char '.')
    return $ SemVer major minor patch release metadata

parseSemVerA :: Parser SemVer
parseSemVerA = SemVer
    <$> integer
    <* char '.'
    <*> integer
    <* char '.'
    <*> integer
    <*> option [] (try $ char '-' >> sepBy pp (char '.'))
    <*> option [] (char '+' >> sepBy pp (char '.'))
        where pp = (NOSS <$> some letter <|> NOSI <$> integer)

--2. integer parsing
parseDigit :: Parser Char
parseDigit = oneOf ['0'..'9'] <?> "digit"

base10Integer :: Parser Integer
base10Integer = read <$> (some parseDigit)
            
--3. integer parsing with negative values
base10Integer' :: Parser Integer
base10Integer' = 
    option (*1) (try $ char '-' >> return (*(-1))) 
    <*> base10Integer

--4. Phone numbers
type NumberingPlanArea = Int -- aka area code
type Exchange = Int
type LineNumber = Int

data PhoneNumber =
    PhoneNumber NumberingPlanArea Exchange LineNumber
    deriving (Eq, Show)

parsePhone :: Parser PhoneNumber
parsePhone =
    PhoneNumber
    <$  optional (char '(')
    <*> (read <$> count 3 digit)
    <*  (optional (oneOf ['-', ')']) >> skipMany (char ' '))
    <*> (read <$> count 3 digit)
    <*  (optional (char '-') >> skipMany (char ' '))
    <*> (read <$> count 4 digit)


















