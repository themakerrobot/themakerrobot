"""
`busio` - Bus protocol support like I2C and SPI
=================================================
See `CircuitPython:busio` in CircuitPython for more details.
* Author(s): cefn
"""
from .board import Pin, spiPorts
from .spi import SPI as _SPI
from .util import Enum, Lockable

class SPI(Lockable):
  """
  Busio SPI Class for CircuitPython Compatibility. Used
  for both MicroPython and Linux.
  """

  def __init__(self, clock, MOSI=None, MISO=None):
    self.deinit()
    for portId, portSck, portMosi, portMiso in spiPorts:
      if (
        (clock == portSck)
        and MOSI in (portMosi, None)  # Clock is required!
        and MISO in (portMiso, None)  # But can do with just output
      ):  # Or just input
        self._spi = _SPI(portId)
        self._pins = (portSck, portMosi, portMiso)
        break
    else:
      raise ValueError(
        "No Hardware SPI on (SCLK, MOSI, MISO)={}\nValid SPI ports:{}".format(
          (clock, MOSI, MISO), spiPorts
        )
      )

  def configure(self, baudrate=100000, polarity=0, phase=0, bits=8):
    """Update the configuration"""
    if self._locked:
      # TODO check if #init ignores MOSI=None rather than unsetting, to save _pinIds attribute
      self._spi.init(
        baudrate=baudrate,
        polarity=polarity,
        phase=phase,
        bits=bits,
        firstbit=_SPI.MSB,
        sck=Pin(self._pins[0].id),
        mosi=Pin(self._pins[1].id),
        miso=Pin(self._pins[2].id),
      )
    else:
      raise RuntimeError("First call try_lock()")

  def deinit(self):
    """Deinitialization"""
    self._spi = None
    self._pinIds = None

  @property
  def frequency(self):
    """Return the baud rate if implemented"""
    try:
      return self._spi.frequency
    except AttributeError:
      raise NotImplementedError(
        "Frequency attribute not implemented for this platform"
      ) from AttributeError

  def write(self, buf, start=0, end=None):
    """Write to the SPI device"""
    return self._spi.write(buf, start, end)

  def readinto(self, buf, start=0, end=None, write_value=0):
    """Read from the SPI device into a buffer"""
    return self._spi.readinto(buf, start, end, write_value=write_value)

  def write_readinto(
    self, buffer_out, buffer_in, out_start=0, out_end=None, in_start=0, in_end=None
  ):
    """Write to the SPI device and read from the SPI device into a buffer"""
    return self._spi.write_readinto(
      buffer_out, buffer_in, out_start, out_end, in_start, in_end
    )
