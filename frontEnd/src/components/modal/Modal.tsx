import React, { useEffect, useRef } from 'react'
import { createPortal } from 'react-dom'

interface ModalProps {
  isOpen: boolean
  onClose: () => void
  title: string
  children: React.ReactNode
}

const Modal: React.FC<ModalProps> = ({ isOpen, onClose, title, children }) => {
  const panelRef = useRef<HTMLDivElement | null>(null)

  useEffect(() => {
    if (!isOpen) return

    // fecha modal ao apertar esc
    const onKey = (e: KeyboardEvent) => {
      if (e.key === 'Escape') onClose()
    }

    // Desativa scroll da página quando o modal está aberto
    document.addEventListener('keydown', onKey)
    const prev = document.body.style.overflow
    document.body.style.overflow = 'hidden'

    setTimeout(() => panelRef.current?.focus(), 0)

    return () => {
      document.removeEventListener('keydown', onKey)
      document.body.style.overflow = prev
    }
  }, [isOpen, onClose])

  if (!isOpen) return null

  return createPortal(
    <div
      className="fixed inset-0 flex items-center justify-center bg-black/50 z-50"
      onMouseDown={onClose}
      aria-hidden={false}
    >
      <div
        role="dialog"
        aria-modal="true"
        aria-labelledby="modal-title"
        ref={panelRef}
        tabIndex={-1}
        className="bg-white rounded-lg shadow-lg p-6 max-w-lg w-full relative"
        onMouseDown={(e) => e.stopPropagation()}
      >
        <h2 id="modal-title" className="text-xl font-semibold mb-4">
          {title}
        </h2>
        <button
          onClick={onClose}
          className="absolute top-3 right-3 text-gray-600"
          aria-label="Fechar modal"
        >
          ×
        </button>
        <div>{children}</div>
      </div>
    </div>,
    document.body
  )
}

export default Modal
