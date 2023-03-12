import time
from functools import wraps

from typing import Callable, Any

TFunc = Callable[..., Any]


def timer(part: str | int, show_result: bool = True, title: str = "",
          show_return: bool = True) -> Callable[..., TFunc]:
    def decorator(f: TFunc) -> TFunc:
        @wraps(f)
        def wrapper(*args, **kwargs) -> Any:
            position = 35
            start_time = time.perf_counter()
            result = f(*args, **kwargs)
            elapsed_time = time.perf_counter() - start_time
            if elapsed_time < 0.1:
                elapsed_time_str = (
                    f"\r\033[{position}C( {(elapsed_time * 1e3):6.3f} ms )"
                )
            else:
                elapsed_time_str = (
                    f"\r\033[{position}C( {elapsed_time:6.3f} s  )"
                )

            if show_result:
                header = title or f"Part {part} answer"
                print("".join([
                    f"{header}: ",
                    f'{result if result is not None and show_return else ""}',
                    elapsed_time_str])
                )
            return result
        return wrapper
    return decorator


class Timer(object):
    title: str
    start_time: float

    def __init__(self, title: str | None = None) -> None:
        self.start_time = 0
        self.title = f"{title} " if title is not None else ''

    def __enter__(self) -> None:
        self.start_time = time.perf_counter()

    def __exit__(self, *info: list[Any]) -> None:
        elapsed_time: float = time.perf_counter() - self.start_time
        elapsed_time_unit: str = "ms" if elapsed_time <= 0.1 else "s"
        elapsed_time = elapsed_time * (1e3 if elapsed_time <= 0.1 else 1)
        print(f'{self.title}{elapsed_time:.3f} {elapsed_time_unit}')
