from dataclasses import dataclass


@dataclass
class MyClass:
    model: int

    def set(self, model: int):
        self.model = model

    def get(self) -> int:
        return self.model
