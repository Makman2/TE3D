# Copyright (C) 2014 Mischa Krüger
# Copyright (C) 2014 Ammar Al-Qaiser
# Copyright (C) 2014 Frank Zimdars
# Copyright (C) 2014 Gordon Kemsies
# Copyright (C) 2014 Lasse Schuirmann
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

default:
	@ echo "Please specify a target."

install:
	@ echo "Invoking recursive make..."
	@ $(MAKE) -C src/ install
