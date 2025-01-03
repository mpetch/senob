; Copyright (C) 2024 Nils Burkard
;
; This program is free software: you can redistribute it and/or modify
; it under the terms of the GNU General Public License as published by
; the Free Software Foundation, either version 3 of the License, or
; (at your option) any later version.
;
; This program is distributed in the hope that it will be useful,
; but WITHOUT ANY WARRANTY; without even the implied warranty of
; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
; GNU General Public License for more details.
;
; You should have received a copy of the GNU General Public License
; along with this program. If not, see <http://www.gnu.org/licenses/>.

global gdt_flush
global tss_flush

gdt_flush:
    mov eax, [esp+4]
    lgdt[eax]

    mov eax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush

.flush:
    ret

tss_flush:
    mov ax, 0x2B    ;not 0x28 because 0x2B are the bottom 2 bits
    ltr ax
    ret   