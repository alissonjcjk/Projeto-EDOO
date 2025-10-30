import { Pencil, Trash2 } from "lucide-react";

export default function EmployeeTable({ employees, onEdit, onDelete }) {
  return (
    <div className="overflow-x-auto bg-white shadow-md rounded-2xl p-4">
      <table className="w-full text-sm text-left text-gray-700">
        <thead className="bg-gray-100 text-gray-800 uppercase text-xs">
          <tr>
            <th className="px-4 py-3">Nome</th>
            <th className="px-4 py-3">Email</th>
            <th className="px-4 py-3">Contato</th>
            <th className="px-4 py-3">Função</th>
            <th className="px-4 py-3">Expediente</th>
            <th className="px-4 py-3">Salário</th>
            <th className="px-4 py-3 text-center">Ações</th>
          </tr>
        </thead>
        <tbody>
          {employees.map((f) => (
            <tr key={f.id} className="border-b hover:bg-gray-50 transition">
              <td className="px-4 py-3 font-medium">{f.nome}</td>
              <td className="px-4 py-3">{f.email}</td>
              <td className="px-4 py-3">{f.contato}</td>
              <td className="px-4 py-3">{f.funcao}</td>
              <td className="px-4 py-3">{f.expediente}</td>
              <td className="px-4 py-3">R$ {f.salario}</td>
              <td className="px-4 py-3 text-center flex justify-center gap-3">
                <button
                  onClick={() => onEdit(f.id)}
                  className="text-blue-600 hover:text-blue-800"
                >
                  <Pencil size={18} />
                </button>
                <button
                  onClick={() => onDelete(f.id)}
                  className="text-red-600 hover:text-red-800"
                >
                  <Trash2 size={18} />
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
    </div>
  );
}
