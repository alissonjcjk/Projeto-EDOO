import { useState, useEffect } from 'react'

interface Props {
  onCancel: () => void
  onSave: (payload: { name: string; price: number; duration: number }) => void
  initial?: { id?: number; nome?: string; name?: string; preco?: number; price?: number; duracao?: number; duration?: number }
}

export default function ServicosForm({ onCancel, onSave, initial }: Props) {
  const [name, setName] = useState(initial?.name || initial?.nome || '')
  const [price, setPrice] = useState(String(initial?.price ?? initial?.preco ?? '0'))
  const [duration, setDuration] = useState(String(initial?.duration ?? initial?.duracao ?? '30'))
  const [error, setError] = useState<string | null>(null)

  useEffect(() => {
    setName(initial?.name || initial?.nome || '')
    setPrice(String(initial?.price ?? initial?.preco ?? '0'))
    setDuration(String(initial?.duration ?? initial?.duracao ?? '30'))
  }, [initial])

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault()
    setError(null)
    if (!name.trim()) return setError('Nome é obrigatório')
    if (Number(price) <= 0) return setError('Preço deve ser maior que zero')
    if (Number(duration) <= 0) return setError('Duração deve ser maior que zero')

    onSave({ name: name.trim(), price: Number(price), duration: Number(duration) })
  }

  return (
    <form className="space-y-4" onSubmit={handleSubmit}>
      {error && <div className="text-red-600">{error}</div>}

      <div>
        <label className="block text-sm font-medium">Nome do Serviço</label>
        <input value={name} onChange={(e) => setName(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="Ex: Corte Masculino" />
      </div>

      <div className="flex gap-4">
        <div className="flex-1">
          <label className="block text-sm font-medium">Preço (R$)</label>
          <input value={price} onChange={(e) => setPrice(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="30.00" />
        </div>
        <div className="w-1/3">
          <label className="block text-sm font-medium">Duração (min)</label>
          <input value={duration} onChange={(e) => setDuration(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="30" />
        </div>
      </div>

      <div className="flex justify-end gap-3 pt-2">
        <button type="button" onClick={onCancel} className="px-4 py-2 rounded bg-white border">Cancelar</button>
        <button type="submit" className="px-4 py-2 rounded bg-black text-white">Salvar</button>
      </div>
    </form>
  )
}
