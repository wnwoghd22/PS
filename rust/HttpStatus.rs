enum HttpStatus<T> {
    NotFound,
    OK(T),
}

impl<T> HttpStatus<T> {
    pub fn code(&self) -> u32 {
        match self {
            HttpStatus::NotFound => 404,
            HttpStatus::OK(_) => 200,
        }
    }
}