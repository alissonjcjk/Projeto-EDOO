import { useState } from 'react'
import { api } from '../../services/api'

interface Props {
  onCancel: () => void
  onSave: (created?: any) => void
}

export default function ClienteForm({ onCancel, onSave }: Props) {
  const [name, setName] = useState('')
  const [email, setEmail] = useState('')
  const [phone, setPhone] = useState('')
  const [saving, setSaving] = useState(false)
  const [error, setError] = useState<string | null>(null)

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault()
    setSaving(true)
    setError(null)
    try {
      const created = await api.createClient({ name, email, phone })
      onSave(created)
    } catch (err) {
      console.error(err)
      setError('Erro ao salvar cliente')
    } finally {
      setSaving(false)
    }
  }

  return (
    <form className="space-y-4" onSubmit={handleSubmit}>
      {error && <div className="text-red-600">{error}</div>}
      <div>
        <label className="block text-sm font-medium">Nome</label>
        <input value={name} onChange={(e) => setName(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="Digite o nome do cliente" />
      </div>

      <div>
        <label className="block text-sm font-medium">Email</label>
        <input value={email} onChange={(e) => setEmail(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="cliente@email.com" />
      </div>

      <div>
        <label className="block text-sm font-medium">Telefone</label>
        <input value={phone} onChange={(e) => setPhone(e.target.value)} className="mt-1 w-full rounded border p-2 bg-gray-50" placeholder="(11) 98765-4321" />
      </div>

      <div className="flex justify-end gap-3 pt-2">
        <button type="button" onClick={onCancel} disabled={saving} className="px-4 py-2 rounded bg-white border">Cancelar</button>
        <button type="submit" disabled={saving} className="px-4 py-2 rounded bg-black text-white">{saving ? 'Salvando...' : 'Salvar'}</button>
      </div>
    </form>
  )
}
