class Chip:
  @property
  def id(self): # pylint: disable=invalid-name,too-many-branches,too-many-return-statements
    return self._linux_id()

  def _linux_id(self): # pylint: disable=too-many-branches
    return "BCM2XXX"

  def __getattr__(self, attr):
    if self.id == attr:
      return True
    return False
