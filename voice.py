import whisper
import sounddevice as sd
from scipy.io.wavfile import write
import os

os.environ["PATH"] += os.pathsep + r"C:\ProgramData\chocolatey\lib\ffmpeg\tools\ffmpeg\bin"

model = whisper.load_model("base")

def record_audio(filename="input.wav", seconds=4, fs=16000):
    audio = sd.rec(int(seconds * fs), samplerate=fs, channels=1)
    sd.wait()
    write(filename, fs, audio)

def speech_to_text(filename="input.wav"):
    result = model.transcribe(filename, language="ru")
    return result["text"]

def listen():
    record_audio()
    text = speech_to_text()
    return text