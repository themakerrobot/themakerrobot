from setuptools import setup, find_packages
from ssd1306_oled import __version__ as VERSION

with open('README.rst') as readme_file:
    readme = readme_file.read()

requirements = [
        'pillow==7.2.0',
]

test_requirements = [
]

setup(
    name='ssd1306_oled',
    version=VERSION,
    description="ssd1306 spi oled package.",
    long_description=readme,
    author="circulus",
    author_email='leeyunjai@circul.us',
    url='https://github.com/themakerrobot/openpibo_models',
    packages            = find_packages(),
    install_requires=requirements,
    keywords='ssd1306',
    classifiers=[
        'Natural Language :: English',
        'Programming Language :: Python :: 3.5',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
    ],
    test_suite='tests',
    tests_require=test_requirements
)
