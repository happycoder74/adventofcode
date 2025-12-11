use std::{
    error::Error,
    fmt::{Debug, Display},
    num::ParseIntError,
    str::FromStr,
};
pub mod part1;
pub mod part2;

type Result<T> = std::result::Result<T, Box<dyn std::error::Error>>;

#[derive(Default, Eq, PartialEq, Clone, Copy, Hash)]
pub enum State {
    On,
    #[default]
    Off,
}

impl std::fmt::Display for State {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{}",
            match self {
                Self::On => '#',
                Self::Off => '.',
            }
        )
    }
}
impl std::fmt::Debug for State {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "{}",
            match self {
                Self::On => '#',
                Self::Off => '.',
            }
        )
    }
}

impl From<ParseIntError> for ParseInstructionError {
    fn from(_: ParseIntError) -> Self {
        ParseInstructionError
    }
}

struct Button {
    toggles: Vec<u32>,
}

impl Debug for Button {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{:?}", self.toggles)
    }
}

impl FromStr for Button {
    type Err = ParseInstructionError;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let buttons: Vec<u32> = s
            .strip_prefix('(')
            .unwrap()
            .strip_suffix(')')
            .unwrap()
            .split(',')
            .map(|b| b.parse().unwrap())
            .collect();
        Ok(Button { toggles: buttons })
    }
}

#[derive(Debug, Clone)]
struct ParseInstructionError;

impl Display for ParseInstructionError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Could not parse instructions")
    }
}

impl Error for ParseInstructionError {}

struct Instruction {
    lights: Vec<State>,
    buttons: Vec<Button>,
    #[allow(unused)]
    joltage: Vec<u32>,
}

impl Display for Instruction {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(
            f,
            "lights: [{}]\nbuttons: {:?}\n",
            self.lights
                .iter()
                .map(|c| match c {
                    State::On => '#',
                    State::Off => '.',
                })
                .collect::<String>(),
            self.buttons
        )
    }
}

impl FromStr for Instruction {
    type Err = ParseInstructionError;
    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let (lights_str, rest) = s.split_once(' ').ok_or(ParseInstructionError)?;
        let (buttons_str, joltage_str) = rest.rsplit_once(' ').ok_or(ParseInstructionError)?;

        let lights: Vec<State> = lights_str
            .chars()
            .skip(1)
            .map_while(|c| match c {
                '.' => Some(State::Off),
                '#' => Some(State::On),
                _ => None,
            })
            .collect();

        let joltage: Vec<u32> = joltage_str
            .strip_prefix('{')
            .unwrap()
            .strip_suffix('}')
            .unwrap()
            .split(',')
            .map(|n| n.parse().unwrap())
            .collect();

        let buttons: Vec<Button> = buttons_str
            .split_whitespace()
            .map(|b| b.parse().unwrap())
            .collect();
        Ok(Self {
            lights,
            buttons,
            joltage,
        })
    }
}

#[derive(Eq, Hash, PartialEq, Clone)]
pub struct Lights {
    lights: Vec<State>,
}

impl Lights {
    fn init(instruction: &Instruction) -> Self {
        Self {
            lights: instruction.lights.iter().map(|_| State::Off).collect(),
        }
    }
}

impl Button {
    fn apply(&self, lights: &Lights) -> Lights {
        let mut return_lights: Vec<State> = lights.lights.clone();
        self.toggles
            .iter()
            .for_each(|b| return_lights[*b as usize].toggle());

        Lights {
            lights: return_lights,
        }
    }
}

impl State {
    fn toggle(&mut self) {
        *self = match *self {
            State::On => State::Off,
            State::Off => State::On,
        }
    }
}
